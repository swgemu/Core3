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

#ifndef TRANSFERITEMMISCCOMMAND_H_
#define TRANSFERITEMMISCCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/building/BuildingObject.h"


class TransferItemMiscCommand : public QueueCommand {
public:

	TransferItemMiscCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		/*StringBuffer infoMsg;
		infoMsg << "target: 0x" << hex << target << " arguments" << arguments.toString();
		creature->info(infoMsg.toString(), true);*/

		StringTokenizer tokenizer(arguments.toString());

		uint64 destinationID = tokenizer.getLongToken();
		int transferType = tokenizer.getIntToken(); // I've seen -1 usually.. 4 when equipping most clothes (I think -1 is remove)
		float unknown1 = tokenizer.getFloatToken();
		float unknown2 = tokenizer.getFloatToken();
		float unknown3 = tokenizer.getFloatToken();

		ManagedReference<SceneObject*> objectToTransfer = server->getZoneServer()->getObject(target);

		if (objectToTransfer == NULL) {
			creature->error("objectToTransfer NULL in transfermisc command");
			return GENERALERROR;
		}

		if (objectToTransfer->isCreatureObject()) {
			//creature->sendSystemMessage("You cant pickup creatures");
			return GENERALERROR;
		}

		SceneObject* objectsParent = objectToTransfer->getParent();

		// TODO: Maybe a better way to handle this. (If its a world loot container, ignore parent) ??
		if (objectsParent != NULL && objectsParent->getGameObjectType() != SceneObject::STATICLOOTCONTAINER) {
			if (objectsParent->isCellObject()) {

				ManagedReference<BuildingObject*> building = (BuildingObject*) objectsParent->getParent();

				if (!building->isOnAdminList(creature)) {
					return GENERALERROR;
				}

				if (objectToTransfer->isTerminal())
					return GENERALERROR;
			} else {
				SceneObject* rootParent = objectToTransfer->getRootParent();

				if (rootParent->isPlayerCreature() && rootParent != creature)
					return GENERALERROR;
			}
		}

		ManagedReference<SceneObject*> destinationObject = server->getZoneServer()->getObject(destinationID);

		if (destinationObject == NULL) {
			creature->error("destinationObject NULL in tansfermisc command");
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

		ZoneServer* zoneServer = server->getZoneServer();
		ObjectController* objectController = zoneServer->getObjectController();

		//TODO: This needs to be looked at more!
		//If transferring the object to a cell, ensure that the creature has permission to drop the item to the cell.
		if (destinationObject->isCellObject()) {
			ManagedReference<BuildingObject*> building = (BuildingObject*) destinationObject->getParent();

			if (!building->isOnAdminList(creature)) {
				return GENERALERROR;
			}

			//Set the objects position to the creature that is transferring it?
			objectToTransfer->initializePosition(creature->getPositionX(), creature->getPositionZ(), creature->getPositionY());
		}

		bool clearWeapon = objectToTransfer->isWeaponObject() && (creature == objectToTransfer->getParent());

		if (!objectController->transferObject(objectToTransfer, destinationObject, transferType, true))
			return GENERALERROR;

		if (clearWeapon)
			creature->setWeapon(NULL, true);

		/*
				if (transferType == -1) {
					SceneObject* parent = objectToTransfer->getParent();

					if (parent == NULL) {
						creature->error("objectToTransfer parent is NULL in transfermisc command");
						return false;
					}

					if (!parent->removeObject(objectToTransfer)) {
						creature->error("could not remove objectToTransfer from parent in transfermisc command");
						return false;
					}

					if (!destinationObject->addObject(objectToTransfer, transferType)) {
						creature->error("could not add objectToTransfer to parent in transfermisc command");
						parent->addObject(objectToTransfer, 4);
						return false;
					}

					player->broadcastMessage(objectToTransfer->link(destinationObject->getObjectID(), 0xFFFFFFFF));

					if (objectToTransfer->isWeaponObject() && player == parent) {
						player->setWeaponID(0, true);
					}
				} else if (transferType == 4) {

				} else {
					creature->error("unknown transferType in transfermisc command");
				}*/
		/*

				//Equip weapon + equip armor never gets here, they have their own CRC, while unequipping of all items WILL go here
				uint64 target = packet->parseLong();
				UnicodeString data;
				packet->parseUnicode(data);

				StringTokenizer tokenizer(data.toString());
				tokenizer.setDelimeter(" ");

				uint64 destinationID = tokenizer.getLongToken();

				//TODO: Pretty sure that this should be called transferType rather than unknown?
				int unknown = tokenizer.getIntToken(); // I've seen -1 usually.. 4 when equipping most clothes (I think -1 is remove)

				float x = tokenizer.getFloatToken();
				float z = tokenizer.getFloatToken();
				float y = tokenizer.getFloatToken();

				TangibleObject* targetTanoObject;

				if (destinationID == player->getObjectID()) { //equipping misc. item to player
					targetTanoObject = (TangibleObject*) player->getInventoryItem(target);

					if (targetTanoObject != NULL) {
						Inventory* inventory = player->getInventory();

						if (inventory != NULL)
							inventory->moveObjectToTopLevel(player, targetTanoObject);

						if(targetTanoObject->isInstrument()) {
							player->changeWeapon(target, true);

						} else if(targetTanoObject->isClothing()) {
							player->changeArmor(target, true);

						} else if(targetTanoObject->isWearableContainer()) {
							player->changeArmor(target, true);
						}

					}

				} else if (destinationID == player->getObjectID() + 1) { //item is going to inventory
					targetTanoObject = (TangibleObject*) player->getInventoryItem(target);

					if (targetTanoObject == NULL){ //the item can't be found in the inventory - maybe a world object?
						Zone* zone = player->getZone();

						//Here we check to see if the player is staff, and if not, we check to see if they have permission to pickup the item in the structure they are in.
						if (player->getAdminLevel() == PlayerCreature* player->isInBuilding()) {
							BuildingObject* building = (BuildingObject*) player->getBuilding();

							if (building != NULL) {
								try {
									building->lock();

									if (building->containsCell(destinationID) && !building->isOnAdminList(player)) {
										player->sendSystemMessage("container_error_message", "container08"); //You do not have permission to access that container.
										building->unlock();
										return false;
									}

									building->unlock();
								} catch (Exception& e) {
									creature->error("Error in ObjectControllerMessage locking building on item pickup");
									building->unlock();
								}
							}
						}

						if (zone != NULL) {
							targetTanoObject = (TangibleObject*) zone->lookupObject(target);
						}
					}

			 		if (targetTanoObject != NULL) {
			 			if(player->isTanoObjEquipped(targetTanoObject)) {

			 				if(targetTanoObject->isWeapon()) {
			 					player->changeWeapon(target, true);

			 				} else if(targetTanoObject->isInstrument()) {
			 					player->changeWeapon(target, true);

			 				} else if(targetTanoObject->isArmor()) {
			 					player->changeArmor(target, true);

			 				} else if(targetTanoObject->isClothing()) {
			 					player->changeArmor(target, true);

			 				} else if(targetTanoObject->isWearableContainer()) {
			 					player->changeArmor(target, true);
			 				}
			 			}

			 		} else {
						//what else object could this be?
			 			return false;
					}

					SceneObject* targetObject = player->getTarget();

					//PlayerCreature* players inventory
					if (targetObject != NULL && targetObject->isNonPlayerCreature()) {
						Creature* creature = (Creature*) targetObject;

						SceneObject* object;

						try {
							creature->wlock(player);

							//if this is null, player isn't looting but moving stuff around in inventory
							object = creature->getLootItem(target);

							creature->unlock();

						} catch (Exception& e) {
							creature->unlock();
						}

						if (object != NULL) {
							player->lootObject(creature, object);
						} else {
							//Current target is a dead creature but player is moving stuff in inventory (because creature->getLootItem returned NULL)
							ManagedReference<TangibleObject*> item = validateDropAction(player, target);

							if (item != NULL)
								transferItemToContainer(player, item, destinationID);

							return true;
						}

					} else {
						//Player has no dead creature as target and dropping an item from a cell or container to the inventory
						ManagedReference<TangibleObject*> item = validateDropAction(player, target);

						if (item != NULL)
							transferItemToContainer(player, item, destinationID);

						return true;
					}

					//Dropping FROM the players inventory TO a cell or container (which could also be a nested inventory container)
				} else {
					ManagedReference<TangibleObject*> item = validateDropAction(player, target);

					//Here we check to see if the player is staff, and if not, we check to see if they have permission to drop the item in the structure they are in.
					if (player->getAdminLevel() == PlayerCreature* player->isInBuilding()) {
						BuildingObject* building = (BuildingObject*) player->getBuilding();

						if (building != NULL) {
							try {
								building->lock();

								if (building->containsCell(destinationID) && !building->isOnAdminList(player)) {
									player->sendSystemMessage("container_error_message", "container08"); //You do not have permission to access that container.
									building->unlock();
									return false;
								}

								building->unlock();
							} catch (Exception& e) {
								creature->error("Unhandled exception in ObjectControllerMessage when trying to lock building and dropping an item.");
								building->unlock();
							}
						}
					}

					if (item != NULL)
						transferItemToContainer(player, item, destinationID);

					return true;
				}*/


		return SUCCESS;
	}

};

#endif //TRANSFERITEMMISCCOMMAND_H_

