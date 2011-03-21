/*
 * StructureObjectImplementation.cpp
 *
 *  Created on: Aug 15, 2010
 *      Author: crush
 */

#include "StructureObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/templates/tangible/SharedStructureObjectTemplate.h"
#include "server/zone/objects/structure/events/StructureMaintenanceTask.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/tangible/sign/SignObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/objects/player/sessions/vendor/CreateVendorSession.h"

#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/inputbox/SuiInputBox.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"

#include "server/zone/templates/appearance/MeshAppearanceTemplate.h"
#include "server/zone/templates/appearance/PortalLayout.h"

void StructureObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	SharedStructureObjectTemplate* structureTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateData);

	lotSize = structureTemplate->getLotSize();

	baseMaintenanceRate = structureTemplate->getBaseMaintenanceRate();

	basePowerRate = structureTemplate->getBasePowerRate();

	length = structureTemplate->getLength();

	width = structureTemplate->getWidth();

	structureTemplate->getPortalLayout();
	structureTemplate->getAppearanceTemplate();
}

void StructureObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	Logger::setLoggingName("StructureObject");
}

void StructureObjectImplementation::finalize() {
}

AABBTree* StructureObjectImplementation::getAABBTree() {
	PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == NULL)
		return NULL;

	MeshAppearanceTemplate* app = portalLayout->getMeshAppearanceTemplate(0);

	return app->getAABBTree();
}

bool StructureObjectImplementation::addPermission(PlayerCreature* player, PlayerCreature* targetPlayer, const String& listName) {
	if (player == NULL || targetPlayer == NULL)
		return false;

	if (listName == "BAN") {
		if (isOwnerOf(targetPlayer)) {
			player->sendSystemMessage("@player_structure:cannot_remove_owner"); //You cannot remove the owner from the admin list.
			return false;
		}

		if (isOnAdminList(targetPlayer)) {
			player->sendSystemMessage("You cannot ban an admin.");
			return false;
		}
	}

	if ((listName == "ENTRY" || listName == "ADMIN") && isOnBanList(targetPlayer)) {
		player->sendSystemMessage("@player_structure:no_banned"); //You cannot add a banned player to the entry list.
		return false;
	}

	if (listName != "BAN" && isOnBanList(targetPlayer)) {
		StringIdChatParameter params;
		params.setStringId("@player_structure:cannot_add_banned"); //%NO must first be removed from the banned list.
		params.setTO(targetPlayer);
		player->sendSystemMessage(params);
		return false;
	}

	bool ret = structurePermissionList.addPermission(targetPlayer->getObjectID(), structurePermissionList.getPermissionFromListName(listName));

	updateToDatabase();

	return ret;
}

bool StructureObjectImplementation::addPermission(PlayerCreature* player, const String& targetPlayerName, const String& listName) {
	PlayerManager* playerManager = server->getPlayerManager();

	if (playerManager == NULL)
		return false;

	ManagedReference<PlayerCreature*> targetPlayer = playerManager->getPlayer(targetPlayerName);

	if (player == NULL || targetPlayer == NULL)
		return false;

	if (listName == "BAN") {
		if (isOwnerOf(targetPlayer)) {
			player->sendSystemMessage("@player_structure:cannot_remove_owner"); //You cannot remove the owner from the admin list.
			return false;
		}

		if (isOnAdminList(targetPlayer)) {
			player->sendSystemMessage("You cannot ban an admin.");
			return false;
		}
	}

	if ((listName == "ENTRY" || listName =="ADMIN") && isOnBanList(targetPlayer)) {
		player->sendSystemMessage("@player_structure:no_banned"); //You cannot add a banned player to the entry list.
		return false;
	}

	if (listName != "BAN" && isOnBanList(targetPlayer)) {
		StringIdChatParameter params;
		params.setStringId("@player_structure:cannot_add_banned"); //%NO must first be removed from the banned list.
		params.setTO(targetPlayer);
		player->sendSystemMessage(params);
		return false;
	}

	bool ret = structurePermissionList.addPermission(targetPlayer->getObjectID(), structurePermissionList.getPermissionFromListName(listName));

	updateToDatabase();

	return ret;
}

bool StructureObjectImplementation::removePermission(PlayerCreature* player, PlayerCreature* targetPlayer, const String& listName) {
	if (player == NULL || targetPlayer == NULL)
		return false;

	if (targetPlayer == player) {
		player->sendSystemMessage("@player_structure:cannot_remove_self"); //You cannot remove yourself from the admin list.
		return false;
	}

	if (isOwnerOf(targetPlayer)) {
		player->sendSystemMessage("@player_structure:cannot_remove_owner"); //You cannot remove the owner from the admin list.
		return false;
	}

	if (listName == "ENTRY" && isOnAdminList(targetPlayer)) {
		player->sendSystemMessage("@player_structure:no_remove_admin"); //You cannot remove an admin from the entry list.
		return false;
	}

	bool ret = structurePermissionList.removePermission(targetPlayer->getObjectID(), structurePermissionList.getPermissionFromListName(listName));

	updateToDatabase();

	return ret;
}

bool StructureObjectImplementation::removePermission(PlayerCreature* player, const String& targetPlayerName, const String& listName) {
	PlayerManager* playerManager = server->getPlayerManager();

	if (playerManager == NULL)
		return false;

	ManagedReference<PlayerCreature*> targetPlayer = playerManager->getPlayer(targetPlayerName);

	if (player == NULL || targetPlayer == NULL)
		return false;

	if (targetPlayer == player) {
		player->sendSystemMessage("@player_structure:cannot_remove_self"); //You cannot remove yourself from the admin list.
		return false;
	}

	if (isOwnerOf(targetPlayer)) {
		player->sendSystemMessage("@player_structure:cannot_remove_owner"); //You cannot remove the owner from the admin list.
		return false;
	}

	if (listName == "ENTRY" && isOnAdminList(targetPlayer)) {
		player->sendSystemMessage("@player_structure:no_remove_admin"); //You cannot remove an admin from the entry list.
		return false;
	}

	bool ret = structurePermissionList.removePermission(targetPlayer->getObjectID(), structurePermissionList.getPermissionFromListName(listName));

	updateToDatabase();

	return ret;
}

String StructureObjectImplementation::getTimeString(uint32 timestamp) {
	String abbrvs[4] = {"seconds", "minutes", "hours", "days"};

	int intervals[4] = {1, 60, 3600, 86400};
	int values[4] = {0, 0, 0, 0};

	StringBuffer str;

	for (int i = 3; i > -1; --i) {
		values[i] = floor(timestamp / intervals[i]);
		timestamp -= values[i] * intervals[i];

		if (values[i] > 0) {
			if (str.length() > 0)
				str << ", ";

			str << ((i == 0) ? "and " : "") << values[i] << " " << abbrvs[i];
		}
	}

	return str.toString();
}


void StructureObjectImplementation::scheduleMaintenanceExpirationEvent() {
	float timeRemaining = surplusMaintenance / baseMaintenanceRate / 3600000;

	maintenanceExpires.updateToCurrentTime();
	maintenanceExpires.addMiliTime(timeRemaining);

	if (structureMaintenanceTask == NULL)
		structureMaintenanceTask = new StructureMaintenanceTask(_this);

	if (structureMaintenanceTask->isScheduled())
		structureMaintenanceTask->reschedule();
	else
		structureMaintenanceTask->schedule(timeRemaining);
}

void StructureObjectImplementation::sendStatusTo(PlayerCreature* player) {
	//TODO: Add in extra status information for administrators.
	//TODO: This needs some refactoring/cleanup
	ManagedReference<SuiListBox*> statusBox = new SuiListBox(player, SuiWindowType::STRUCTURE_STATUS);
	statusBox->setPromptTitle("@player_structure:structure_status_t"); //Structure Status
	statusBox->setUsingObject(_this);

	if (isInstallationObject())
		((InstallationObject*) _this)->updateInstallationWork();

	String full = getCustomObjectName().toString();

	if (getCustomObjectName().isEmpty())
		getObjectName()->getFullPath(full);

	statusBox->setPromptText("@player_structure:structure_name_prompt " + full); //Structure Name:

	ManagedReference<PlayerCreature*> playerCreature = dynamic_cast<PlayerCreature*>(getZoneServer()->getObject(getOwnerObjectID()));

	if (playerCreature == NULL)
		return;

	statusBox->addMenuItem("@player_structure:owner_prompt  " + playerCreature->getFirstName());

	if (isBuildingObject() && _this == player->getDeclaredResidence())
			statusBox->addMenuItem("@player_structure:declared_residency"); //You have declared your residency here.

	if (isPublicStructure())
		statusBox->addMenuItem("@player_structure:structure_public"); //This structure is public
	else
		statusBox->addMenuItem("@player_structure:structure_private"); //This structure is private

	StringBuffer sscond, ssmpool, ssmrate, ssppool, ssprate, ssnitems;

	sscond << dec << "@player_structure:condition_prompt " << ((int) (((getMaxCondition() - getConditionDamage()) / getMaxCondition()) * 100)) << "%";
	statusBox->addMenuItem(sscond.toString());

	int maintpool = getSurplusMaintenance();
	int maintrate = getBaseMaintenanceRate();

	ssmpool << dec << "@player_structure:maintenance_pool_prompt " << maintpool; //Maintenance Pool:

	if (maintpool > 0) {
		uint32 seconds = (uint32) floor(((float) maintpool) / (((float) maintrate) / 3600.0f));
		ssmpool << dec << " (" << getTimeString(seconds) << ")";
	}

	statusBox->addMenuItem(ssmpool.toString());

	ssmrate << dec << "@player_structure:maintenance_rate_prompt " << maintrate << " cr/hr";
	statusBox->addMenuItem(ssmrate.toString());

	if (isInstallationObject() && !((InstallationObject*) _this)->isGeneratorObject()) {
		ssppool << dec << "@player_structure:power_reserve_prompt " << (int) getSurplusPower();
		statusBox->addMenuItem(ssppool.toString());

		ssprate << dec << "@player_structure:power_consumption_prompt " << (int) getBasePowerRate() << " @player_structure:units_per_hour";
		statusBox->addMenuItem(ssprate.toString());
	}

	if (isBuildingObject()) {
		//TODO: Count items that can be picked up by the player (exclude terminals like structure, elevator, guild)...
		ssnitems << dec << "@player_structure:items_in_building_prompt " << ((BuildingObjectImplementation*)this)->getCurrentNumerOfPlayerItems(); //Number of Items in Building:

		statusBox->addMenuItem(ssnitems.toString());
	}

	player->addSuiBox(statusBox);
	player->sendMessage(statusBox->generateMessage());
}

void StructureObjectImplementation::sendDestroyConfirmTo(PlayerCreature* player) {
	if (!isOwnerOf(player)) {
		player->sendSystemMessage("@player_structure:destroy_must_be_owner"); //You must be the owner to destroy a structure.
		return;
	}

	String full = getCustomObjectName().toString();

	if (getCustomObjectName().isEmpty())
		getObjectName()->getFullPath(full);

	String red = "\\#FF6347";
	String green = "\\#32CD32";
	String close = "\\#.";

	String no = red + " @player_structure:can_redeed_no_suffix " + close;
	String yes = green + " @player_structure:can_redeed_yes_suffix " + close;

	String redeed = (isRedeedable()) ? yes : no;

	StringBuffer maint;
	maint << "@player_structure:redeed_maintenance " << ((isRedeedable()) ? green : red) << getSurplusMaintenance() << "/" << getRedeedCost() << close;

	StringBuffer entry;
	entry << "@player_structure:confirm_destruction_d1 ";
	entry << "@player_structure:confirm_destruction_d2 \n\n";
	entry << "@player_structure:confirm_destruction_d3a ";
	entry << green << " @player_structure:confirm_destruction_d3b " << close << " ";
	entry << "@player_structure:confirm_destruction_d4 \n";
	entry << "@player_structure:redeed_confirmation " << redeed;

	StringBuffer cond;
	cond << "@player_structure:redeed_condition \\#32CD32 " << (getMaxCondition() - getConditionDamage()) << "/" << getMaxCondition() << "\\#.";

	ManagedReference<SuiListBox*> destroybox = new SuiListBox(player, SuiWindowType::STRUCTURE_DESTROY_CONFIRM);
	destroybox->setCancelButton(true, "@no");
	destroybox->setOkButton(true, "@yes");
	destroybox->setUsingObject(_this);
	destroybox->setPromptTitle(full);
	destroybox->setPromptText(entry.toString());
	destroybox->addMenuItem("@player_structure:can_redeed_alert " + redeed);
	destroybox->addMenuItem(cond.toString());
	destroybox->addMenuItem(maint.toString());

	player->addSuiBox(destroybox);
	player->sendMessage(destroybox->generateMessage());
}

void StructureObjectImplementation::sendDestroyCodeTo(PlayerCreature* player) {
	if (!isOwnerOf(player)) {
		player->sendSystemMessage("@player_structure:destroy_must_be_owner"); //You must be the owner to destroy a structure.
		return;
	}

	//Generate a new destroy code.
	uint32 destroyCode = generateDestroyCode();

	String red = "\\#FF6347";
	String green = "\\#32CD32";
	String close = "\\#.";

	String no = red + " @player_structure:will_not_redeed_confirm " + close;
	String yes = green + " @player_structure:will_redeed_confirm " + close;

	String redeed = (isRedeedable()) ? yes : no;

	StringBuffer entry;
	entry << "@player_structure:your_structure_prefix ";
	entry << redeed << " @player_structure:will_redeed_suffix \n\n";
	entry << "Code: " << destroyCode;

	SuiInputBox* destroycodebox = new SuiInputBox(player, SuiWindowType::STRUCTURE_DESTROY_CODE, 0);
	destroycodebox->setUsingObject(_this);
	destroycodebox->setPromptTitle("@player_structure:confirm_destruction_t"); //Confirm Structure Deletion
	destroycodebox->setPromptText(entry.toString());
	destroycodebox->setCancelButton(true, "@cancel");
	destroycodebox->setMaxInputSize(6);

	player->addSuiBox(destroycodebox);
	player->sendMessage(destroycodebox->generateMessage());
	return;
}

void StructureObjectImplementation::sendManageMaintenanceTo(PlayerCreature* player) {
	int availableCredits = player->getCashCredits();

	if (availableCredits <= 0) {
		player->sendSystemMessage("@player_structure:no_money"); //You do not have any money to pay maintenance.
		return;
	}

	StringBuffer sstext;

	ManagedReference<SuiTransferBox*> maintenanceBox = new SuiTransferBox(player, SuiWindowType::STRUCTURE_MANAGE_MAINTENANCE);
	maintenanceBox->setPromptTitle("@player_structure:select_amount");
	maintenanceBox->setUsingObject(_this);

	int surplusMaintenance = getSurplusMaintenance();

	sstext << "@player_structure:select_maint_amount \n" << "@player_structure:current_maint_pool " << surplusMaintenance;
	maintenanceBox->setPromptText(sstext.toString());

	maintenanceBox->addFrom("@player_structure:total_funds", String::valueOf(availableCredits), String::valueOf(availableCredits), "1");
	maintenanceBox->addTo("@player_structure:to_pay", "0", "0", "1");

	player->addSuiBox(maintenanceBox);
	player->sendMessage(maintenanceBox->generateMessage());

	//Calculate how much time until the maintenance will expire.
	//structureObject->scheduleMaintenanceExpirationEvent();
}

void StructureObjectImplementation::sendChangeNamePromptTo(PlayerCreature* player) {
	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::OBJECT_NAME, 0x00);

	inputBox->setPromptTitle("@sui:set_name_title");
	inputBox->setPromptText("@sui:set_name_prompt");
	inputBox->setUsingObject(_this);
	inputBox->setMaxInputSize(255);

	if (isBuildingObject()) {
		BuildingObject* buildingObject = (BuildingObject*) _this;

		if (buildingObject->getSignObject() != NULL) {
			ManagedReference<SignObject*> sign = buildingObject->getSignObject();
			inputBox->setDefaultInput(sign->getObjectName()->getCustomString().toString());
		}
	} else {
		inputBox->setDefaultInput(objectName.getCustomString().toString());
	}

	player->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

bool StructureObjectImplementation::isOwnerOf(SceneObject* obj) {
	if (obj->isPlayerCreature() && ((PlayerCreature*) obj)->getPlayerObject()->isPrivileged())
		return true;

	return obj->getObjectID() == ownerObjectID;
}

bool StructureObjectImplementation::isOwnerOf(uint64 objid) {
	ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(objid);

	//We have to check if the id belongs to an admin...perhaps we should have a list on playermanager of admin objectids...
	if (obj != NULL && obj->isPlayerCreature()) {
		PlayerCreature* player = (PlayerCreature*) obj.get();

		if (player->getPlayerObject()->isPrivileged())
			return true;
	}

	return objid == ownerObjectID;
}

void StructureObjectImplementation::createVendor(PlayerCreature* player) {
	if (!isPublicStructure()) {
		player->sendSystemMessage("@player_structure:vendor_no_private");
		return;
	}

	//Create Session
	ManagedReference<CreateVendorSession*> session = new CreateVendorSession(player);
	session->initalizeWindow(player);

	player->addActiveSession(SessionFacadeType::CREATEVENDOR, session);

}
