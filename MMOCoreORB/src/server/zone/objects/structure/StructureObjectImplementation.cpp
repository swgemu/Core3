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
