/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TRANSFERITEMWEAPONCOMMAND_H_
#define TRANSFERITEMWEAPONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sessions/TradeSession.h"

class TransferItemWeaponCommand : public QueueCommand {
public:

	TransferItemWeaponCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		creature->info("transfer item weapon");

		StringBuffer infoMsg;
		infoMsg << "target: 0x" << hex << target << " arguments" << arguments.toString();
		creature->info(infoMsg.toString());

		StringTokenizer tokenizer(arguments.toString());

		uint64 destinationID = tokenizer.getLongToken();
		int transferType = tokenizer.getIntToken(); // I've seen -1 usually.. 4 when equipping most clothes (I think -1 is remove)
		float unknown1 = tokenizer.getFloatToken();
		float unknown2 = tokenizer.getFloatToken();
		float unknown3 = tokenizer.getFloatToken();

		ManagedReference<TradeSession*> tradeContainer = creature->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		if (tradeContainer != NULL) {
			server->getZoneServer()->getPlayerManager()->handleAbortTradeMessage(creature);
		}

		ManagedReference<SceneObject*> objectToTransfer = server->getZoneServer()->getObject(target);

		if (objectToTransfer == NULL) {
			creature->error("objectToTransfer NULL in transferItemWeapon command");
			return GENERALERROR;
		}

		if (!objectToTransfer->checkContainerPermission(creature, ContainerPermissions::MOVECONTAINER))
			return GENERALERROR;

		ManagedReference<SceneObject*> objectsParent = objectToTransfer->getParent().get();

		if (objectsParent == NULL)
			return GENERALERROR;

		if (!objectsParent->checkContainerPermission(creature, ContainerPermissions::MOVEOUT))
			return GENERALERROR;

		if (!objectToTransfer->isWeaponObject() && !objectToTransfer->isInstrument() && !objectToTransfer->isFishingPoleObject()) {
			creature->error("objectToTransfer is neither a weapon object nor an instrument/fishing pole in transferItemWeapon");
			return GENERALERROR;
		}

		if (!objectToTransfer->isASubChildOf(creature))
			return GENERALERROR;

		ManagedReference<SceneObject*> destinationObject = server->getZoneServer()->getObject(destinationID);

		if (destinationObject == NULL) {
			creature->error("destinationObject NULL in tansferItemWeapon command");
			return GENERALERROR;
		}

		if (destinationObject != creature) {
			creature->error("destinationObject is not creature in transferItemWeapon command");
			return GENERALERROR;
		}

		if (transferType == 4) {
			ManagedReference<SceneObject*> parent = objectToTransfer->getParent().get();

			if (parent == NULL) {
				creature->error("objectToTransfer parent is NULL in transferItemWeapon command");
				return GENERALERROR;
			}

			ZoneServer* zoneServer = server->getZoneServer();
			ObjectController* objectController = zoneServer->getObjectController();

			String errorDescription;
			int transferPreProcess = destinationObject->canAddObject(objectToTransfer, transferType, errorDescription);

			if (transferPreProcess == TransferErrorCode::SLOTOCCUPIED) {
				int arrangementSize = objectToTransfer->getArrangementDescriptorSize();

				if (arrangementSize > 0) {
					const String& childArrangement = objectToTransfer->getArrangementDescriptor(0)->get(0);

					ManagedReference<SceneObject*> objectToRemove = destinationObject->getSlottedObject(childArrangement);

					if (!objectController->transferObject(objectToRemove, parent, -1, true, true))
						return GENERALERROR;

					if (!objectController->transferObject(objectToTransfer, destinationObject, transferType, true)) {
						objectController->transferObject(objectToRemove, destinationObject, transferType, true);
						return GENERALERROR;
					}
				}
			} else if (transferPreProcess != 0) {
				if (errorDescription.length() > 1)
					creature->sendSystemMessage(errorDescription);

				return GENERALERROR;
			} else {
				if (!objectController->transferObject(objectToTransfer, destinationObject, transferType, true))
					return GENERALERROR;
			}

			if (creature == destinationObject) {

				if (objectToTransfer->isWeaponObject()) {
					WeaponObject* weaponObject = cast<WeaponObject*>( objectToTransfer.get());

					creature->setWeapon(weaponObject, true);

					if (creature->isPlayerCreature()) {
						CreatureObject* playerCreature = creature;

						if (weaponObject->isCertifiedFor(playerCreature)) {
							weaponObject->setCertified(true);
						} else {
							playerCreature->sendSystemMessage("@combat_effects:no_proficiency"); //You lack the necessary skills to use this weapon properly. Damage with this weapon will be greatly reduced
							weaponObject->setCertified(false);
						}

						PlayerObject* ghost = playerCreature->getPlayerObject();

						if (creature->hasBuff(STRING_HASHCODE("centerofbeing")))
							creature->removeBuff(STRING_HASHCODE("centerofbeing"));

						ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();
						if (playerManager != NULL) {
							creature->setLevel(playerManager->calculatePlayerLevel(creature));
						}
					}

				}
			}

		} else {
			creature->error("unknown transferType in transferItemWeapon command");
		}

		return SUCCESS;
	}

};

#endif //TRANSFERITEMWEAPONCOMMAND_H_

