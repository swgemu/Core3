/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef TRANSFERITEMWEAPONCOMMAND_H_
#define TRANSFERITEMWEAPONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"


class TransferItemWeaponCommand : public QueueCommand {
public:

	TransferItemWeaponCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringBuffer infoMsg;
		infoMsg << "target: 0x" << hex << target << " arguments" << arguments.toString();
		creature->info(infoMsg.toString());

		StringTokenizer tokenizer(arguments.toString());

		uint64 destinationID = tokenizer.getLongToken();
		int transferType = tokenizer.getIntToken(); // I've seen -1 usually.. 4 when equipping most clothes (I think -1 is remove)
		float unknown1 = tokenizer.getFloatToken();
		float unknown2 = tokenizer.getFloatToken();
		float unknown3 = tokenizer.getFloatToken();

		ManagedReference<SceneObject*> objectToTransfer = server->getZoneServer()->getObject(target);

		if (objectToTransfer == NULL) {
			creature->error("objectToTransfer NULL in transfermiscweapon command");
			return GENERALERROR;
		}

		if (!objectToTransfer->isWeaponObject() && !objectToTransfer->isInstrument() && !objectToTransfer->isFishingPoleObject()) {
			creature->error("objectToTransfer is neither a weapon object nor an instrument/fishing pole in transferitemweapon");
			return GENERALERROR;
		}

		if (!objectToTransfer->isASubChildOf(creature))
			return GENERALERROR;

		ManagedReference<SceneObject*> destinationObject = server->getZoneServer()->getObject(destinationID);

		if (destinationObject == NULL) {
			creature->error("destinationObject NULL in tansfermiscweapon command");
			return GENERALERROR;
		}

		if (destinationObject != creature) {
			creature->error("destinationObject is not creature in transfermiscweapon command");
			return GENERALERROR;
		}

		if (transferType == 4) {
			SceneObject* parent = objectToTransfer->getParent();

			if (parent == NULL) {
				creature->error("objectToTransfer parent is NULL in transfermiscweapon command");
				return GENERALERROR;
			}

			ZoneServer* zoneServer = server->getZoneServer();
			ObjectController* objectController = zoneServer->getObjectController();

			String errorDescription;
			int transferPreProcess = destinationObject->canAddObject(objectToTransfer, transferType, errorDescription);

			if (transferPreProcess == TransferErrorCode::SLOTOCCUPIED) {
				int arrangementSize = objectToTransfer->getArrangementDescriptorSize();

				if (arrangementSize > 0) {
					String childArrangement = objectToTransfer->getArrangementDescriptor(0);

					ManagedReference<SceneObject*> objectToRemove = destinationObject->getSlottedObject(childArrangement);

					if (!objectController->transferObject(objectToRemove, parent, 0xFFFFFFFF, true))
						return GENERALERROR;
				}
			} else if (transferPreProcess != 0) {
				if (errorDescription.length() > 1)
					creature->sendSystemMessage(errorDescription);

				return GENERALERROR;
			}

			if (!objectController->transferObject(objectToTransfer, destinationObject, transferType, true))
				return GENERALERROR;

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

						if (ghost->getCenteredBonus() != 0) {
							Reference<Task*> task = playerCreature->getPendingTask("centerofbeing");
							if (task != NULL) {
								task->cancel();
								task->run();
							}
						}
					}

				}
			}

		} /*else if (transferType == 4) {

				}*/ else {
					creature->error("unknown transferType in transfermiscweapon command");
				}



		/*uint64 target = packet->parseLong();

			TangibleObject* targetTanoObject;
			targetTanoObject = cast<TangibleObject*>( creature->getInventoryItem(target));

			if (targetTanoObject != NULL) {
				Inventory* inventory = creature->getInventory();

				if (inventory != NULL)
					inventory->moveObjectToTopLevel(creature, targetTanoObject);

				creature->changeWeapon(target, true);
			}*/


		return SUCCESS;
	}

};

#endif //TRANSFERITEMWEAPONCOMMAND_H_

