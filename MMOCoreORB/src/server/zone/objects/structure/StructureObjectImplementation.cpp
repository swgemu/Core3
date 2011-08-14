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
#include "server/zone/templates/tangible/SharedStructureObjectTemplate.h"

void StructureObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	SharedStructureObjectTemplate* structureTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateData);

	lotSize = structureTemplate->getLotSize();

	baseMaintenanceRate = structureTemplate->getBaseMaintenanceRate();

	basePowerRate = structureTemplate->getBasePowerRate();

	structureTemplate->getPortalLayout();
	structureTemplate->getAppearanceTemplate();
}

void StructureObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	Logger::setLoggingName("StructureObject");
}

void StructureObjectImplementation::finalize() {
}

int StructureObjectImplementation::getLotSize() {
	SharedStructureObjectTemplate* ssot = dynamic_cast<SharedStructureObjectTemplate*>(templateObject.get());

	if (ssot == NULL)
		return 0;

	return ssot->getLotSize();
}

AABBTree* StructureObjectImplementation::getAABBTree() {
	PortalLayout* portalLayout = templateObject->getPortalLayout();

	if (portalLayout == NULL)
		return NULL;

	MeshAppearanceTemplate* app = portalLayout->getMeshAppearanceTemplate(0);

	return app->getAABBTree();
}

String StructureObjectImplementation::getTimeString(uint32 timestamp) {
	String abbrvs[4] = {"seconds", "minutes", "hours", "days"};

	int intervals[4] = {1, 60, 3600, 86400};
	int values[4] = {0, 0, 0, 0};

	StringBuffer str;

	for (int i = 3; i > -1; --i) {
		values[i] = floor((float)(timestamp / intervals[i]));
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

void StructureObjectImplementation::sendStatusTo(CreatureObject* player) {
	//TODO: Add in extra status information for administrators.
	//TODO: This needs some refactoring/cleanup
	ManagedReference<SuiListBox*> statusBox = new SuiListBox(player, SuiWindowType::STRUCTURE_STATUS);
	statusBox->setPromptTitle("@player_structure:structure_status_t"); //Structure Status
	statusBox->setUsingObject(_this);
	PlayerObject* ghost = player->getPlayerObject();

	if (isInstallationObject())
		((InstallationObjectImplementation*) this)->updateInstallationWork();

	String full = getCustomObjectName().toString();

	if (getCustomObjectName().isEmpty())
		getObjectName()->getFullPath(full);

	statusBox->setPromptText("@player_structure:structure_name_prompt " + full); //Structure Name:

	ManagedReference<CreatureObject*> playerCreature = dynamic_cast<CreatureObject*>(getZoneServer()->getObject(getOwnerObjectID()));

	if (playerCreature == NULL)
		return;

	statusBox->addMenuItem("@player_structure:owner_prompt  " + playerCreature->getFirstName());

	if (isBuildingObject() && _this == ghost->getDeclaredResidence())
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

	if (isInstallationObject() && !((InstallationObjectImplementation*) this)->isGeneratorObject()) {
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

	player->getPlayerObject()->addSuiBox(statusBox);
	player->sendMessage(statusBox->generateMessage());
}

void StructureObjectImplementation::sendManageMaintenanceTo(CreatureObject* player) {
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

	player->getPlayerObject()->addSuiBox(maintenanceBox);
	player->sendMessage(maintenanceBox->generateMessage());

	//Calculate how much time until the maintenance will expire.
	//structureObject->scheduleMaintenanceExpirationEvent();
}

void StructureObjectImplementation::sendChangeNamePromptTo(CreatureObject* player) {
	ManagedReference<SuiInputBox*> inputBox = new SuiInputBox(player, SuiWindowType::OBJECT_NAME, 0x00);

	inputBox->setPromptTitle("@sui:set_name_title");
	inputBox->setPromptText("@sui:set_name_prompt");
	inputBox->setUsingObject(_this);
	inputBox->setMaxInputSize(255);
	inputBox->setDefaultInput(objectName.getCustomString().toString());

	player->getPlayerObject()->addSuiBox(inputBox);
	player->sendMessage(inputBox->generateMessage());
}

bool StructureObjectImplementation::isOwnerOf(SceneObject* obj) {

	if (obj->isCreatureObject()) {
		ManagedReference<PlayerObject*> ghost = ((CreatureObject*) obj)->getPlayerObject();

		if (ghost->isPrivileged())
			return true;
	}

	return obj->getObjectID() == ownerObjectID;
}

bool StructureObjectImplementation::isOwnerOf(uint64 objid) {
	ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(objid);

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* player = (CreatureObject*) obj.get();

		if (player->getPlayerObject()->isPrivileged())
			return true;
	}

	return objid == ownerObjectID;
}

void StructureObjectImplementation::createVendor(CreatureObject* player) {
	if (!isPublicStructure()) {
		player->sendSystemMessage("@player_structure:vendor_public_only");
		return;
	}

	//Create Session
	ManagedReference<CreateVendorSession*> session = new CreateVendorSession(player);
	session->initalizeWindow(player);

}
