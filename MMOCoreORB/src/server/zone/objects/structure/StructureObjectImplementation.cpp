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

//Only gets called when maintenance has been changed by an outside source
void StructureObjectImplementation::scheduleMaintenanceExpirationEvent() {
	updateStructureStatus();

	int timeRemaining = (int) (surplusMaintenance * 3600.f / baseMaintenanceRate);

	maintenanceExpires.updateToCurrentTime();
	maintenanceExpires.addMiliTime(timeRemaining * 1000);

	if (structureMaintenanceTask == NULL)
		structureMaintenanceTask = new StructureMaintenanceTask(_this);

	if (structureMaintenanceTask->isScheduled())
		structureMaintenanceTask->reschedule(timeRemaining);
	else
		structureMaintenanceTask->schedule(timeRemaining);
}

bool StructureObjectImplementation::isOwnerOf(SceneObject* obj) {
	if (obj->isCreatureObject()) {
		ManagedReference<PlayerObject*> ghost = (cast<CreatureObject*>( obj))->getPlayerObject();

		if (ghost->isPrivileged())
			return true;
	}

	return obj->getObjectID() == ownerObjectID;
}

bool StructureObjectImplementation::isOwnerOf(uint64 objid) {
	ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(objid);

	if (obj != NULL && obj->isPlayerCreature()) {
		CreatureObject* player = cast<CreatureObject*>( obj.get());

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

void StructureObjectImplementation::updateStructureStatus() {
	/** Points when updateStructureStatus should occur:
	 * Prior to inserting or withdrawing maintenance or power, and after the deposit/withdrawal.
	 * When requesting a Structure Status report.
	 * Any time the maintenance or power surplus is changed by a hand other than this method.
	 */
	float timeDiff = ((float) lastUpdateTimestamp.miliDifference()) / 1000.f;
	lastUpdateTimestamp.updateToCurrentTime();

	float maintenanceDue = ((float) baseMaintenanceRate / 3600.f) * timeDiff;
	float powerDue = ((float) basePowerRate / 3600.f) * timeDiff;

	if (surplusMaintenance > 0.f)
		surplusMaintenance -= maintenanceDue;
	//else start ticking off condition and sending emails

	if (surplusPower > 0.f)
		surplusPower -= powerDue;
	//else if installation, shutdown.
}
