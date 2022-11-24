/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TRANSFERITEMMISCCOMMAND_H_
#define TRANSFERITEMMISCCOMMAND_H_

#include "server/ServerCore.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sessions/TradeSession.h"
#include "server/zone/objects/transaction/TransactionLog.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/scene/TransferErrorCode.h"
#include "QueueCommand.h"

class TransferItemMiscCommand : public QueueCommand {
public:
	TransferItemMiscCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		/*creature->info("transfer item misc");

		StringBuffer infoMsg;
		infoMsg << "target: 0x" << hex << target << " arguments" << arguments.toString();
		creature->info(infoMsg.toString(), true);*/

		StringTokenizer tokenizer(arguments.toString());

		if (!tokenizer.hasMoreTokens())
			return GENERALERROR;

		uint64 destinationID = tokenizer.getLongToken();
		int transferType = tokenizer.getIntToken(); // containment type .. -1 container, >=4 slotted container
		float unknown1 = tokenizer.getFloatToken();
		float unknown2 = tokenizer.getFloatToken();
		float unknown3 = tokenizer.getFloatToken();

		ManagedReference<TradeSession*> tradeContainer = creature->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		if (tradeContainer != nullptr) {
			server->getZoneServer()->getPlayerManager()->handleAbortTradeMessage(creature);
		}

		auto objectToTransfer = server->getZoneServer()->getObject(target);

		if (objectToTransfer == nullptr) {
			creature->error("objectToTransfer nullptr in transferItemMisc command");
			return GENERALERROR;
		}

		auto destinationObject = server->getZoneServer()->getObject(destinationID);

		if (destinationObject == nullptr) {
			creature->error("destinationObject nullptr in tansferItemMisc command");
			return GENERALERROR;
		}

		auto src = TransactionLog::getTrxParticipant(objectToTransfer->getParent().get(), creature);
		auto dst = TransactionLog::getTrxParticipant(destinationObject, destinationObject);

		TransactionLog trx(src, dst, objectToTransfer, TrxCode::TRANSFERITEMMISC);

		if (trx.isVerbose()) {
			// Include extra details
			trx.addState("creature", creature->getObjectID());
			trx.addState("target", target);
			trx.addRelatedObject(target, true);
			trx.addState("arguments", arguments.toString());
			trx.addState("destinationID", destinationID);
			trx.addState("transferType", transferType);
			trx.addState("destinationClassName", destinationObject->_getClassName());
		}

		// Filter noisy stuff
		if (destinationObject->isCellObject() && (objectToTransfer->isCreature() || objectToTransfer->isDroidObject())) {
			trx.discard();
		}

		return doTransferItemMisc(creature, objectToTransfer, destinationObject, transferType, trx);
	}

	int static doTransferItemMisc(CreatureObject* creature, SceneObject* objectToTransfer, SceneObject* destinationObject, int transferType, TransactionLog& trx) {
		trx.addState("transferType", transferType);

		if (objectToTransfer == nullptr) {
			creature->error("objectToTransfer nullptr in transferItemMisc command");
			trx.abort() << "objectToTransfer nullptr";
			return GENERALERROR;
		}

		if (destinationObject == nullptr) {
			creature->error("destinationObject nullptr in tansferItemMisc command");
			trx.abort() << "destinationObject nullptr";
			return GENERALERROR;
		}

		if (destinationObject->isIntangibleObject()) {
			trx.abort() << "destinationObject is IntangibleObject";
			return GENERALERROR;
		}

		if (objectToTransfer->isClientObject() || (!objectToTransfer->isTangibleObject())){
			if (!objectToTransfer->isManufactureSchematic()){
				trx.abort() << "expected objectToTransfer to be ManufactureSchematic";
				return GENERALERROR;
			}
		}

		if (!objectToTransfer->checkContainerPermission(creature, ContainerPermissions::MOVECONTAINER)) {
			creature->sendSystemMessage("@error_message:perm_no_move");
			trx.abort() << "No permission to move objectToTransfer";
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> objectsParent = objectToTransfer->getParent().get();

		if (objectsParent == nullptr) {
			trx.abort() << "Failed to get parent";
			return GENERALERROR;
		}

		if(objectToTransfer->isVendor() && !objectsParent->checkContainerPermission(creature, ContainerPermissions::MOVEVENDOR)){
			trx.abort() << "Not allowed to move vendor from parent";
			return GENERALERROR;
		}

		if (!objectToTransfer->isVendor() && !objectsParent->checkContainerPermission(creature, ContainerPermissions::MOVEOUT)){
			trx.abort() << "Not allowed to move object out of parent";
			return GENERALERROR;
		}

		for (int i = 0; i < objectToTransfer->getArrangementDescriptorSize(); ++i) {
			const Vector<String>* descriptors = objectToTransfer->getArrangementDescriptor(i);
			for (int j = 0; j < descriptors->size(); ++j) {
				const String& descriptor = descriptors->get(j);

				if (descriptor == "inventory" || descriptor == "datapad" || descriptor == "default_weapon"
						|| descriptor == "mission_bag" || descriptor == "ghost" || descriptor == "bank" || descriptor == "hair"){
					trx.abort() << "Attempted to transfer " << descriptor;
					return GENERALERROR;
				}
			}
		}

		// Check for any parent that is containerType == NONE
		for (auto parent = objectToTransfer->getParent().get(); parent != nullptr; parent = parent->getParent().get()) {
			Locker clocker(parent, creature);

			if (parent->getContainerType() == ContainerType::NONE) {
				creature->error() << "Trying to remove object from containerType==NONE: oid " << parent->getObjectID();
				trx.abort() << "Attempted to transfer from containerType == NONE";
				creature->sendSystemMessage("@error_message:perm_no_move");
				return GENERALERROR;
			}
		}

		ManagedReference<SceneObject*> parent = objectToTransfer->getParent().get();

		// Check bank transfer
		SceneObject* bank = creature->getSlottedObject("bank");

		if (bank != nullptr && (bank == destinationObject || bank == parent) && !creature->isNearBank()) {
			trx.discard();
			return TOOFAR;
		}

		Zone* zoneObject = objectToTransfer->getZone();

		if (zoneObject != nullptr) {
			ManagedReference<SceneObject*> rootParent = objectToTransfer->getRootParent();

			float maxDistance =  16.5;

			if (rootParent != nullptr && !rootParent->isBuildingObject() && parent != nullptr && !parent->isBuildingObject()) {
				float rootDist = rootParent->getDistanceTo(creature);

				if (rootDist > maxDistance) { // Handles Hoppers in Factories
					trx.abort() << "Too far from root: " << (int)rootDist;
					return TOOFAR;
				}

				ManagedReference<SceneObject*> destParent = destinationObject->getParent().get();

				if (destParent != nullptr) {
					if (destParent->isCellObject()) {
						destParent = destinationObject;
					}

					float destDistance = destParent->getDistanceTo(creature);
					ManagedReference<SceneObject*> destGrandParent = destParent->getParent().get();

					if (((destinationObject->isContainerObject() && destGrandParent != nullptr && destGrandParent->isCellObject()) || destParent->isInstallationObject() || destParent->isCraftingStation()) && destDistance > maxDistance) {
						trx.abort() << "Too far from root: " << (int)destinationObject->getParent().get()->getDistanceTo(creature);
						return TOOFAR;
					}
				}
			} else {
				ManagedReference<SceneObject*> par = nullptr;
				ManagedReference<SceneObject*> obj = objectToTransfer;

				if (rootParent->containsChildObject(objectToTransfer)){
					trx.abort() << "objectToTransfer contained in rootParent";
					return INVALIDTARGET;
				}

				// Container Inside Cell to Player Transfer

				while ((par = obj->getParent().get()) != nullptr) {
					if (par->isCellObject()) {
						float distance = obj->getDistanceTo(creature);

						if (distance > maxDistance) {
							trx.abort() << "Too far from creature: " << (int)distance;
							return TOOFAR;
						} else {
							break;
						}
					} else {
						obj = par;
					}
				}

				// Player Inside Cell to Container Transfer

				obj = objectToTransfer;

				while ((par = obj->getParent().get()) != nullptr) {
					if (par == creature) {
						ManagedReference<SceneObject*> destPar = destinationObject->getParent().get();

						if (destPar != nullptr) {
							ManagedReference<SceneObject*> destGrandParent = destPar->getParent().get();
							ManagedReference<SceneObject*> inventory = creature->getSlottedObject("inventory");

							if (destPar == creature || destinationObject->isCellObject() || (destGrandParent != nullptr && inventory != nullptr && (destGrandParent == inventory || destPar == inventory))) {
								break;
							} else if (destPar->isCellObject()) {
								destPar = destinationObject;
							}

							float distance = destPar->getDistanceTo(creature);

							if (distance > maxDistance) {
								trx.abort() << "Too far from creature: " << (int)distance;
								return TOOFAR;
							} else {
								break;
							}
						} else {
							break;
						}
					} else {
						obj = par;
					}
				}
			}
		} else {
			creature->error("trying to transfer an object with null zone");
			trx.abort() << "objectToTransfer has nullptr zone";
			return GENERALERROR;
		}

		String errorDescription;
		int errorNumber = 0;

		if ((errorNumber = destinationObject->canAddObject(objectToTransfer, transferType, errorDescription)) != 0) {
			if (errorDescription.length() > 1)
				creature->sendSystemMessage(errorDescription);
			else
				creature->error() << "cannot add objectToTransfer to destinationObject: errorNumber: " << errorNumber << " destinationID: " << destinationObject->getObjectID();
			if (errorNumber == TransferErrorCode::CONTAINERFULL || errorNumber == TransferErrorCode::NOTNEARBANK) {
				// Very noisy and not really useful
				trx.discard();
			} else {
				trx.addState("transferErrorCode", errorNumber);
				trx.abort() << "canAddObject failed: " << errorNumber << " - " << errorDescription;
			}
			return GENERALERROR;
		}

		if(destinationObject->isCellObject()) {
			if (creature->getParent().get() != destinationObject) {
				creature->sendSystemMessage("@player_structure:not_valid_location"); //That is not a valid location.
				trx.abort() << "Not valid location";
				return GENERALERROR;
			}

			Vector3 endPoint(creature->getPositionX(), creature->getPositionY(), creature->getPositionZ());

			if (!CollisionManager::checkLineOfSightInParentCell(creature, endPoint)) {
				creature->sendSystemMessage("@player_structure:not_valid_location"); //That is not a valid location.
				trx.abort() << "Out of line of sight";
				return GENERALERROR;
			}
		}
		if(objectToTransfer->isManufactureSchematic() && !destinationObject->isDataPad()) {
			trx.abort() << "ManufactureSchematic but destination is not data pad";
			return GENERALERROR;
		}

		if (objectToTransfer->isVendor() && !destinationObject->checkContainerPermission(creature, ContainerPermissions::MOVEVENDOR)) {
			trx.abort() << "Not allowed to move vendor to destinationObject";
			return GENERALERROR;
		}

		if (!objectToTransfer->isVendor() && !destinationObject->checkContainerPermission(creature, ContainerPermissions::MOVEIN)) {
			trx.abort() << "Not allowed to move object into destinationObject";
			return GENERALERROR;
		}

		ZoneServer* zoneServer = ServerCore::getZoneServer();
		ObjectController* objectController = zoneServer->getObjectController();

		objectToTransfer->initializePosition(creature->getPositionX(), creature->getPositionZ(), creature->getPositionY());

		bool clearWeapon = objectToTransfer->isWeaponObject() && (creature == objectToTransfer->getParent().get());

		bool notifyLooted = (objectToTransfer->getParentRecursively(SceneObjectType::CREATURE) != nullptr || objectToTransfer->getParentRecursively(SceneObjectType::NPCCREATURE) != nullptr);

		bool notifyContainerContentsChanged = (objectToTransfer->getParentRecursively(SceneObjectType::STATICLOOTCONTAINER) != nullptr || (objectToTransfer->getParentRecursively(SceneObjectType::CONTAINER)) != nullptr);

		Locker clocker(objectsParent, creature);

		if (!objectController->transferObject(objectToTransfer, destinationObject, transferType, true)){
			trx.abort() << "transferObject failed";
			return GENERALERROR;
		}

		if (clearWeapon) {
			creature->setWeapon(nullptr, true);

			if (creature->hasBuff(STRING_HASHCODE("centerofbeing")))
				creature->removeBuff(STRING_HASHCODE("centerofbeing"));

			ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();
			if (playerManager != nullptr) {
				creature->setLevel(playerManager->calculatePlayerLevel(creature));
			}
		}

		if (notifyLooted) {
			objectToTransfer->notifyObservers(ObserverEventType::ITEMLOOTED, creature, 0);
		}

		if (notifyContainerContentsChanged)
			objectsParent->notifyObservers(ObserverEventType::CONTAINERCONTENTSCHANGED, creature, 0);

		trx.commit();
		return SUCCESS;
	}
};

#endif //TRANSFERITEMMISCCOMMAND_H_
