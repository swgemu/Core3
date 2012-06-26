/*
 * InstallationObjectMenuComponent.cpp
 *
 *  Created on: Feb 27, 2012
 *      Author: xyborn
 */

#include "InstallationObjectMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

void InstallationObjectMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (!sceneObject->isInstallationObject())
		return;

	InstallationObject* installation = cast<InstallationObject*>(sceneObject);

	if (!installation->isOnAdminList(player))
		return;

	menuResponse->addRadialMenuItem(118, 3, "@player_structure:management");
	menuResponse->addRadialMenuItemToRadialID(118, 128, 3, "@player_structure:permission_destroy"); //Destroy Structure
	menuResponse->addRadialMenuItemToRadialID(118, 124, 3, "@player_structure:management_status"); //Status
	menuResponse->addRadialMenuItemToRadialID(118, 129, 3, "@player_structure:management_pay"); //Pay Maintenance
	menuResponse->addRadialMenuItemToRadialID(118, 50, 3, "@base_player:set_name"); //Set Name

	if (!installation->isGeneratorObject()) {
		menuResponse->addRadialMenuItemToRadialID(118, 51, 3, "@player_structure:management_power"); //Deposit Power
	}

	menuResponse->addRadialMenuItem(117, 3, "@player_structure:permissions"); //Structure Permissions
	menuResponse->addRadialMenuItemToRadialID(117, 121, 3, "@player_structure:permission_admin"); //Administrator List
	menuResponse->addRadialMenuItemToRadialID(117, 123, 3, "@player_structure:permission_hopper"); //Hopper List

	/// Temp for log viewing
	menuResponse->addRadialMenuItemToRadialID(118, 72, 3, "@space/story_loot_n:loot_tatooine_hutt"); //a Log

}

int InstallationObjectMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (!sceneObject->isInstallationObject())
		return 1;

	InstallationObject* installation = cast<InstallationObject*>(sceneObject);

	ManagedReference<Zone*> zone = installation->getZone();

	if (zone == NULL)
		return 1;

	if (!installation->isOnAdminList(player))
		return 1;

	ManagedReference<StructureManager*> structureManager = zone->getStructureManager();

	if (structureManager == NULL)
		return 1;

	switch (selectedID) {
	case 124:
		player->executeObjectControllerAction(0x13F7E585, installation->getObjectID(), ""); //structureStatus
		break;

	case 129:
		player->executeObjectControllerAction(0xE7E35B30, installation->getObjectID(), ""); //payMaintenance
		break;

	case 128:
		player->executeObjectControllerAction(0x18FC1726, installation->getObjectID(), ""); //destroyStructure command
		break;

	case 50:
		structureManager->promptNameStructure(player, installation, installation);
		//player->executeObjectControllerAction(0xC367B461, installation->getObjectID(), ""); //nameStructure
		break;

	case 51:
		//TODO: Move to structure manager.
		if (!installation->isGeneratorObject()) {
			installation->handleStructureAddEnergy(player);
		}
		break;

	case 121:
		installation->sendPermissionListTo(player, "ADMIN");
		break;

	case 123:
		installation->sendPermissionListTo(player, "HOPPER");
		break;

	case 72:
		if(true) {
			/// 2 sui's, log of what is happening / happened
			/// and items in hopper
			HopperList* hopper = installation->getHopperList();
			ManagedReference<SuiListBox*> contents = new SuiListBox(player);
			contents->setPromptTitle("Items");
			contents->setPromptText("Contents of this harvester");
			for(int i = 0; i < hopper->size(); ++i) {
				ResourceContainer* container = hopper->get(i);
				if(container != NULL)
					contents->addMenuItem(container->getSpawnName() + " : " + container->getQuantity(), 0);
			}
			if(hopper->size() == 0)
				contents->addMenuItem("Empty", 0);

			player->sendMessage(contents->generateMessage());

			ManagedReference<SuiMessageBox*> logs = new SuiMessageBox(player, 0);
			logs->setPromptTitle("Log");

			Vector<String>* logList = installation->getLogs();
			StringBuffer builder;
			for(int i = 0; i < logList->size(); ++i) {
				builder << logList->get(i) << "\n";
			}
			logs->setPromptText(builder.toString());

			player->sendMessage(logs->generateMessage());
		}

		break;

	default:
		break;
	}

	return 0;
}


