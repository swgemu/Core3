/*
 * InstallationObjectImplementation.cpp
 *
 *  Created on: Jun 4, 2010
 *      Author: crush
 */

#include "InstallationObject.h"
#include "server/zone/packets/installation/InstallationObjectMessage3.h"
#include "server/zone/packets/installation/InstallationObjectMessage6.h"

#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"

void InstallationObjectImplementation::sendBaselinesTo(SceneObject* player) {
	//send buios here
	info("sending installation baselines");

	BaseMessage* buio3 = new InstallationObjectMessage3(_this);
	player->sendMessage(buio3);

	BaseMessage* buio6 = new InstallationObjectMessage6(_this);
	player->sendMessage(buio6);
}

void InstallationObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	//All objects in a cell can be picked up, if the player is on the structures permission list.
	//This opens the door to allow admins to be able to drop/pickup items in public structures

	if (!isOnAdminList(player))
		return;

	menuResponse->addRadialMenuItem(122, 1, "@player_structure:management");
	menuResponse->addRadialMenuItemToRadialID(122, 128, 3, "@player_structure:permission_destroy");
	menuResponse->addRadialMenuItemToRadialID(122, 124, 3, "@player_structure:management_status");
	menuResponse->addRadialMenuItemToRadialID(122, 50, 3, "@ui_radial:set_name");
	menuResponse->addRadialMenuItemToRadialID(122, 129, 3, "@player_structure:management_pay");

	/*if (objectSubType == TangibleObjectImplementation::HARVESTER ||
			objectSubType == TangibleObjectImplementation::GENERATOR)
		management->addRadialMenuItem(78, 3, "@harvester:manage");

	if(objectSubType == TangibleObjectImplementation::HARVESTER)
		management->addRadialMenuItem(77, 3, "@player_structure:management_power");

	*/
}

int InstallationObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	switch (selectedID) {
	/*case 122:
		sendPermissionListTo(player, "ADMIN");
		break;*/

	case 124:
		handleStructureStatus(player);
		break;

	case 129:
		handleStructureManageMaintenance(player);
		break;

	case 128:
		handleStructureDestroy(player);
		break;

	case 50:
		handleSetObjectName(player);
		break;

	default:
		break;
	}

	return 0;
}

void InstallationObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	TangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);

	if (!destroyContainedObjects)
		return;

	ManagedReference<SceneObject*> deed = getZoneServer()->getObject(deedObjectID);

	if (deed != NULL)
		deed->destroyObjectFromDatabase(true);
}

void InstallationObjectImplementation::handleStructureDestroy(PlayerCreature* player) {
	removeFromZone();

	destroyObjectFromDatabase(true);
}

void InstallationObjectImplementation::handleSetObjectName(PlayerCreature* player) {
	ManagedReference<SuiInputBox*> setTheName = new SuiInputBox(player, SuiWindowType::OBJECT_NAME, 0x00);

	setTheName->setPromptTitle("@sui:set_name_title");
	setTheName->setPromptText("@sui:set_name_prompt");
	setTheName->setUsingObject(_this);

	player->addSuiBox(setTheName);
	player->sendMessage(setTheName->generateMessage());
}

void InstallationObjectImplementation::handleStructureStatus(PlayerCreature* player) {
	StringBuffer sscond, ssmpool, ssmrate, ssppool, ssprate;

	ManagedReference<SuiListBox*> statusBox = new SuiListBox(player, SuiWindowType::INSTALLATION_STATUS, 0x01);
	statusBox->setPromptTitle("@player_structure:structure_status_t");
	String full;
	objectName.getFullPath(full);
	statusBox->setPromptText("@player_structure:structure_name_prompt " + full);

	ManagedReference<PlayerCreature*> playerCreature = (PlayerCreature*) getZoneServer()->getObject(ownerObjectID);
	statusBox->addMenuItem("@player_structure:owner_prompt  " + playerCreature->getFirstName());

	if (publicStructure)
		statusBox->addMenuItem("@player_structure:structure_now_public");
	else
		statusBox->addMenuItem("@player_structure:structure_now_private");

	sscond << dec << "@player_structure:condition_prompt " << ((int) (((maxCondition - conditionDamage) / maxCondition) * 100)) << "%";
	statusBox->addMenuItem(sscond.toString());

	ssmpool << dec << "@player_structure:maintenance_pool_prompt " << (int) surplusMaintenance;
	statusBox->addMenuItem(ssmpool.toString());

	ssmrate << dec << "@player_structure:maintenance_rate_prompt " << (int) baseMaintenanceRate << " @player_structure:units_per_hour";
	statusBox->addMenuItem(ssmrate.toString());

	ssppool << dec << "@player_structure:power_reserve_prompt " << (int) surplusPower;
	statusBox->addMenuItem(ssppool.toString());

	ssprate << dec << "@player_structure:power_consumption_prompt " << (int) basePowerRate << " @player_structure:units_per_hour";
	statusBox->addMenuItem(ssprate.toString());

	player->addSuiBox(statusBox);
	player->sendMessage(statusBox->generateMessage());
}


void InstallationObjectImplementation::handleStructureManageMaintenance(PlayerCreature* player) {
	try {
		StringBuffer sstext, sscash, ssmaintenance;

		ManagedReference<SuiTransferBox*> maintenanceBox = new SuiTransferBox(player, SuiWindowType::MANAGE_MAINTENANCE);
		maintenanceBox->setUsingObject(_this);
		maintenanceBox->setPromptTitle("@player_structure:select_amount");

		sstext << "@player_structure:select_maint_amount \n"
			   << "@player_structure:current_maint_pool " << (int)surplusMaintenance;
		maintenanceBox->setPromptText(sstext.toString());

		sscash << player->getCashCredits();
		ssmaintenance << surplusMaintenance;

		maintenanceBox->addFrom("@player_structure:total_funds", sscash.toString(), sscash.toString(), "1");
		maintenanceBox->addTo("@player_structure:to_pay", ssmaintenance.toString(), ssmaintenance.toString(), "1");

		player->addSuiBox(maintenanceBox);
		player->sendMessage(maintenanceBox->generateMessage());

	} catch(...) {
		System::out << "unreported exception in InstallationObjectImplementation::handleStructureManageMaintenance\n";
	}
}

