/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TRANSFERITEMMISCCOMMAND_H_
#define TRANSFERITEMMISCCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sessions/TradeSession.h"

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

		creature->info("transfer item misc");

		/*
		StringBuffer infoMsg;
		infoMsg << "target: 0x" << hex << target << " arguments" << arguments.toString();
		creature->info(infoMsg.toString(), true); */

		StringTokenizer tokenizer(arguments.toString());

		uint64 destinationID = tokenizer.getLongToken();
		int transferType = tokenizer.getIntToken(); // containment type .. -1 container, >=4 slotted container
		float unknown1 = tokenizer.getFloatToken();
		float unknown2 = tokenizer.getFloatToken();
		float unknown3 = tokenizer.getFloatToken();

		ManagedReference<TradeSession*> tradeContainer = creature->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		if (tradeContainer != NULL) {
			server->getZoneServer()->getPlayerManager()->handleAbortTradeMessage(creature);
		}

		ManagedReference<SceneObject*> objectToTransfer = server->getZoneServer()->getObject(target);

		if (objectToTransfer == NULL) {
			creature->error("objectToTransfer NULL in transferItemMisc command");
			return GENERALERROR;
		}

		if (objectToTransfer->isClientObject() || (!objectToTransfer->isTangibleObject())){
			if (!objectToTransfer->isManufactureSchematic()){
				return GENERALERROR;
			}
		}

		if (!objectToTransfer->checkContainerPermission(creature, ContainerPermissions::MOVECONTAINER)) {
			creature->sendSystemMessage("@error_message:perm_no_move");
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> objectsParent = objectToTransfer->getParent().get();

		if (objectsParent == NULL) {
			return GENERALERROR;
		}

		if(objectToTransfer->isVendor() && !objectsParent->checkContainerPermission(creature, ContainerPermissions::MOVEVENDOR)){
			return GENERALERROR;
		}

		if (!objectToTransfer->isVendor() && !objectsParent->checkContainerPermission(creature, ContainerPermissions::MOVEOUT)){
			return GENERALERROR;
		}

		for (int i = 0; i < objectToTransfer->getArrangementDescriptorSize(); ++i) {
			const Vector<String>* descriptors = objectToTransfer->getArrangementDescriptor(i);
			for (int j = 0; j < descriptors->size(); ++j) {
				const String& descriptor = descriptors->get(j);

				if (descriptor == "inventory" || descriptor == "datapad" || descriptor == "default_weapon"
						|| descriptor == "mission_bag" || descriptor == "ghost" || descriptor == "bank" || descriptor == "hair"){
					return GENERALERROR;
				}
			}
		}

		Zone* zoneObject = objectToTransfer->getZone();

		if (zoneObject != NULL) {
			ManagedReference<SceneObject*> rootParent = objectToTransfer->getRootParent();

			float maxDistance = 12.5;

			if (!rootParent->isBuildingObject()) {
				if (rootParent->getDistanceTo(creature) > maxDistance) {
					return TOOFAR;
				}
			} else {
				ManagedReference<SceneObject*> par = NULL;
				ManagedReference<SceneObject*> obj = objectToTransfer;

				if (rootParent->containsChildObject(objectToTransfer)){
					return INVALIDTARGET;
				}

				while ((par = obj->getParent().get()) != NULL) {
					if (par->isCellObject()) {
						if (obj->getDistanceTo(creature) > maxDistance) {
							return TOOFAR;
						}
						else
							break;
					} else {
						obj = par;
					}
				}
			}
		} else {
			creature->error("trying to transfer an object with null zone");
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> destinationObject = server->getZoneServer()->getObject(destinationID);

		if (destinationObject == NULL) {
			creature->error("destinationObject NULL in tansferItemMisc command");
			return GENERALERROR;
		}

		if (destinationObject->isIntangibleObject()) {
			return GENERALERROR;
		}

		String errorDescription;
		int errorNumber = 0;

		if ((errorNumber = destinationObject->canAddObject(objectToTransfer, transferType, errorDescription)) != 0) {
			if (errorDescription.length() > 1)
				creature->sendSystemMessage(errorDescription);
			else
				creature->error("cannot add objectToTransfer to destinationObject " + String::valueOf(errorNumber));
			return GENERALERROR;
		}

		if(destinationObject->isCellObject()) {
			if (creature->getParent().get() != destinationObject) {
				creature->sendSystemMessage("@player_structure:not_valid_location"); //That is not a valid location.
				return GENERALERROR;
			}

			Vector3 endPoint(creature->getPositionX(), creature->getPositionY(), creature->getPositionZ());

			if (!CollisionManager::checkLineOfSightInParentCell(creature, endPoint)) {
				creature->sendSystemMessage("@player_structure:not_valid_location"); //That is not a valid location.
				return GENERALERROR;
			}
		}
		if(objectToTransfer->isManufactureSchematic() && !destinationObject->isDataPad()) {
			return GENERALERROR;
		}

		if (objectToTransfer->isVendor() && !destinationObject->checkContainerPermission(creature, ContainerPermissions::MOVEVENDOR)) {
			return GENERALERROR;
		}

		if (!objectToTransfer->isVendor() && !destinationObject->checkContainerPermission(creature, ContainerPermissions::MOVEIN)) {
			return GENERALERROR;
		}

		ZoneServer* zoneServer = server->getZoneServer();
		ObjectController* objectController = zoneServer->getObjectController();

		objectToTransfer->initializePosition(creature->getPositionX(), creature->getPositionZ(), creature->getPositionY());

		bool clearWeapon = objectToTransfer->isWeaponObject() && (creature == objectToTransfer->getParent().get());

		bool notifyLooted = (objectToTransfer->getParentRecursively(SceneObjectType::CREATURE) != NULL || objectToTransfer->getParentRecursively(SceneObjectType::NPCCREATURE) != NULL);

		bool notifyContainerContentsChanged = (objectToTransfer->getParentRecursively(SceneObjectType::STATICLOOTCONTAINER) != NULL);

		Locker clocker(objectsParent, creature);

		if (!objectController->transferObject(objectToTransfer, destinationObject, transferType, true)){
			return GENERALERROR;
		}

		if (clearWeapon) {
			creature->setWeapon(NULL, true);

			if (creature->hasBuff(STRING_HASHCODE("centerofbeing")))
				creature->removeBuff(STRING_HASHCODE("centerofbeing"));

			ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();
			if (playerManager != NULL) {
				creature->setLevel(playerManager->calculatePlayerLevel(creature));
			}
		}

		if (notifyLooted) {
			objectToTransfer->notifyObservers(ObserverEventType::ITEMLOOTED, creature, 0);
		}

		if (notifyContainerContentsChanged)
			objectsParent->notifyObservers(ObserverEventType::CONTAINERCONTENTSCHANGED, creature, 0);

		return SUCCESS;
	}

};

#endif //TRANSFERITEMMISCCOMMAND_H_

