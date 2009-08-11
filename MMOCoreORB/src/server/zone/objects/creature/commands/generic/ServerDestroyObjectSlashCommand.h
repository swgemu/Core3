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

#ifndef SERVERDESTROYOBJECTSLASHCOMMAND_H_

#define SERVERDESTROYOBJECTSLASHCOMMAND_H_


#include "../../../scene/SceneObject.h"
/*#include "../../../../managers/item/ItemManager.h"
#include "../../../waypoint/WaypointObject.h"
#include "../../../tangible/Container.h"
#include "../../../tangible/Inventory.h"
#include "../../../tangible/crafting/CraftingTool.h"

#include "../../../intangible/IntangibleObject.h"
#include "../../../creature/CreatureObject.h"
#include "../../../creature/pet/CreaturePet.h"*/

class ServerDestroyObjectSlashCommand : public QueueCommand {
public:

	ServerDestroyObjectSlashCommand(const String& name, ZoneProcessServerImplementation* server)
		: QueueCommand(name, server) {

	}

	bool doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return false;

		if (!checkInvalidPostures(creature))
			return false;

		/*
		uint64 objid = packet->parseLong(); //get the id

		ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

		if (player->getTradeSize() != 0) {
			player->sendSystemMessage("You cant destroy objects while trading..");
			return false;
		}

		UnicodeString unkPramString;
		packet->parseUnicode(unkPramString); //?

		ManagedReference<WaypointObject> waypoint = player->getWaypoint(objid);
		ManagedReference<SceneObject> datapadData =  player->getDatapadItem(objid);
		ManagedReference<SceneObject> invObj = player->getInventoryItem(objid);
		ManagedReference<SceneObject> bankObj = player->getBankItem(objid);

		//Avoid redundant code:
		if (bankObj != NULL)
			invObj = bankObj;

		if (invObj != NULL && invObj->isTangible()) {
			TangibleObject* tano = (TangibleObject*) invObj.get();

			if (tano->isEquipped()) {
				player->unequipItem(tano);
			}

			if (tano->isContainer()) {
				Container* container = (Container*) tano;

				while (!container->isContainerEmpty()) {
					ManagedReference<SceneObject> sco = container->getObject(0);

					itemManager->deletePlayerItem(player, ((TangibleObject*) sco.get()), true);

					container->removeObject(0);
					sco->removeFromZone(true);
					sco->finalize();
				}
			}

			//System::out << "Server destroy happening\n";

			if (tano->isCraftingTool()) {
				CraftingTool* tool = (CraftingTool*) tano;

				if (!tool->isReady()) {
					player->sendSystemMessage("You cant delete a working crafting tool!");
					return false;
				}
			}

			itemManager->deletePlayerItem(player, tano, true);

			//Move item to inventory top level for deletion
			Inventory* inventory = player->getInventory();
			if (inventory != NULL)
				inventory->moveObjectToTopLevel(player, tano);

			player->removeInventoryItem(objid);

			if (player->getWeapon() == tano)
				player->setWeapon(NULL);

			if (player->getSurveyTool() == tano)
				player->setSurveyTool(NULL);

			BaseMessage* msg = new SceneObjectDestroyMessage(tano);
			player->getClient()->sendMessage(msg);

			tano->finalize();

		} else if (waypoint != NULL) {
			if (player->removeWaypoint(waypoint))
				waypoint->finalize();

		} else if (datapadData != NULL) {

			if (datapadData->isIntangible()) {
				IntangibleObject* itno = (IntangibleObject*)datapadData.get();
				SceneObject* worldObject = itno->getWorldObject();

				if (worldObject->isNonPlayerCreature()) {
					CreatureObject* crea = (Creature*) worldObject;
					if (crea->isPet()) {
						try {
							((CreaturePet*)crea)->wlock();
							((CreaturePet*)crea)->store(false);
							((CreaturePet*)crea)->unlock();
						} catch (...) {
							System::out << "Unreported exception caught in RadialManager::handlePetCall\n";
							((CreaturePet*)crea)->unlock();
						}
					}
				}
			}

			player->removeDatapadItem(objid);

			itemManager->deleteDatapadItem(player, datapadData.get(), true);

			BaseMessage* msg = new SceneObjectDestroyMessage(datapadData);
			player->getClient()->sendMessage(msg);

			SceneObject* linkedItem = datapadData.get()->getObject(0);

			datapadData->finalize();

			if(linkedItem != NULL) {

				if(linkedItem->isNonPlayerCreature() && linkedItem == (CreatureObject*)player->getMount())
					player->setMount(NULL);

				linkedItem->finalize();
				msg = new SceneObjectDestroyMessage(linkedItem);
				player->getClient()->sendMessage(msg);
			}
		}*/
		return true;
	}

};

#endif //SERVERDESTROYOBJECTSLASHCOMMAND_H_

