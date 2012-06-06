/*
 * GeneratorObjectImplementation.cpp
 *
 *  Created on: 15/06/2010
 *      Author: victor
 */


#include "GeneratorObject.h"
#include "server/zone/packets/harvester/HarvesterObjectMessage7.h"
#include "server/zone/packets/installation/InstallationObjectDeltaMessage7.h"
#include "server/zone/objects/resource/ResourceSpawn.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/harvester/ResourceHarvesterActivatePageMessage.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/objects/area/ActiveArea.h"

void GeneratorObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (!isOnAdminList(player))
		return;

	InstallationObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	menuResponse->addRadialMenuItemToRadialID(118, 78, 3, "@harvester:manage"); //Operate Machinery
}

void GeneratorObjectImplementation::synchronizedUIListen(SceneObject* player, int value) {
	if (!player->isPlayerCreature() || !isOnAdminList(cast<CreatureObject*>(player)) || getZone() == NULL)
		return;

	addOperator(cast<CreatureObject*>(player));

	updateInstallationWork();

	HarvesterObjectMessage7* msg = new HarvesterObjectMessage7(_this.get());
	player->sendMessage(msg);

	activateUiSync();
}

void GeneratorObjectImplementation::synchronizedUIStopListen(SceneObject* player, int value) {
	if (!player->isPlayerCreature())
		return;

	removeOperator(cast<CreatureObject*>(player));
}

int GeneratorObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (!isOnAdminList(player))
		return 1;

	switch (selectedID) {

	case 78: {
		ResourceHarvesterActivatePageMessage* rhapm = new ResourceHarvesterActivatePageMessage(getObjectID());
		player->sendMessage(rhapm);
		break;
	}

	default:
		return InstallationObjectImplementation::handleObjectMenuSelect(player, selectedID);
	}

	return 0;
}
