/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef TRANSFERITEMARMORCOMMAND_H_
#define TRANSFERITEMARMORCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sessions/TradeSession.h"

class TransferItemArmorCommand : public QueueCommand {
public:

	TransferItemArmorCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		creature->info("transfer item armor");

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
			creature->error("objectToTransfer NULL in transferitemarmor command");
			return GENERALERROR;
		}

		if (!objectToTransfer->checkContainerPermission(creature, ContainerPermissions::MOVECONTAINER))
			return GENERALERROR;

		ManagedReference<SceneObject*> objectsParent = objectToTransfer->getParent().get();

		if (objectsParent == NULL)
			return GENERALERROR;

		if (!objectsParent->checkContainerPermission(creature, ContainerPermissions::MOVEOUT))
			return GENERALERROR;

		if (!objectToTransfer->isWearableObject()) {
			creature->error("objectToTransfer is not an armor object in transferitemarmor");
			return GENERALERROR;
		}

		if (!objectToTransfer->isASubChildOf(creature))
			return GENERALERROR;

		ManagedReference<SceneObject*> destinationObject = server->getZoneServer()->getObject(destinationID);

		if (destinationObject == NULL) {
			creature->error("destinationObject NULL in transferitemarmor command");
			return GENERALERROR;
		}

		if (destinationObject != creature) {
			creature->error("destinationObject is not player in transferitemarmor command");
			return GENERALERROR;
		}

		if (transferType == 4) {
			ManagedReference<SceneObject*> parent = objectToTransfer->getParent().get();

			if (parent == NULL) {
				creature->error("objectToTransfer parent is NULL in transferitemarmor command");
				return GENERALERROR;
			}

			ZoneServer* zoneServer = server->getZoneServer();
			ObjectController* objectController = zoneServer->getObjectController();

			String errorDescription;
			int transferPreProcess = destinationObject->canAddObject(objectToTransfer, transferType, errorDescription);

			if (transferPreProcess == TransferErrorCode::SLOTOCCUPIED) {
				int arrangementSize = objectToTransfer->getArrangementDescriptorSize();

				if (arrangementSize > 0) {
					int arrangementGroupToUse = -1;

					for (int i = 0; i < arrangementSize && arrangementGroupToUse == -1; ++i) {
						const Vector<String>* descriptors = objectToTransfer->getArrangementDescriptor(i);

						for (int j = 0; j < descriptors->size(); ++j) {
							const String& descriptor = descriptors->get(j);

							if (destinationObject->getSlottedObject(descriptor) == NULL && arrangementGroupToUse == -1) {
								arrangementGroupToUse = i;
							} else if (arrangementGroupToUse != -1) {
								arrangementGroupToUse = -1;
								break;
							}
						}
					}

					if (arrangementGroupToUse != -1) {
						transferType += arrangementGroupToUse;
					} else {
						const String& childArrangement = objectToTransfer->getArrangementDescriptor(0)->get(0);

						ManagedReference<SceneObject*> objectToRemove = destinationObject->getSlottedObject(childArrangement);

						if (objectToRemove == NULL)
							return GENERALERROR;

						if (!objectController->transferObject(objectToRemove, parent, 0xFFFFFFFF, true))
							return GENERALERROR;
					}
				}
			} else if (transferPreProcess != 0) {
				if (errorDescription.length() > 1)
					creature->sendSystemMessage(errorDescription);

				return GENERALERROR;
			}

			if (!objectController->transferObject(objectToTransfer, destinationObject, transferType, true))
				return GENERALERROR;

		} /*else if (transferType == 4) {

						}*/ else {
							creature->error("unknown transferType in transferitemarmor command");
						}

		/*

				uint64 target = packet->parseLong();

				TangibleObject* targetTanoObject;
				targetTanoObject = cast<TangibleObject*>( player->getInventoryItem(target));

				if (targetTanoObject != NULL) {
					Inventory* inventory = player->getInventory();

					if (inventory != NULL)
						inventory->moveObjectToTopLevel(player, targetTanoObject);

					player->changeArmor(target, false);
				}*/

		return SUCCESS;
	}

};

#endif //TRANSFERITEMARMORCOMMAND_H_

