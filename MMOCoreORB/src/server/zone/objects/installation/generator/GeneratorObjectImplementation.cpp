/*
 * GeneratorObjectImplementation.cpp
 *
 *  Created on: 15/06/2010
 *      Author: victor
 */

#include "server/zone/objects/installation/generator/GeneratorObject.h"
#include "server/zone/packets/harvester/HarvesterObjectMessage7.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/harvester/ResourceHarvesterActivatePageMessage.h"

void GeneratorObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (!isOnAdminList(player))
		return;

	InstallationObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	menuResponse->addRadialMenuItemToRadialID(118, 78, 3, "@harvester:manage"); //Operate Machinery
}

void GeneratorObjectImplementation::synchronizedUIListen(CreatureObject* player, int value) {
	if (!player->isPlayerCreature() || !isOnAdminList(player) || getZone() == NULL)
		return;

	addOperator(player);

	updateInstallationWork();

	HarvesterObjectMessage7* msg = new HarvesterObjectMessage7(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(msg);

	activateUiSync();
}

void GeneratorObjectImplementation::synchronizedUIStopListen(CreatureObject* player, int value) {
	if (!player->isPlayerCreature())
		return;

	removeOperator(player);
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

String GeneratorObjectImplementation::getRedeedMessage() {

	if(operating)
		return "destroy_deactivate_first";

	if(getHopperSize() > 0)
		return "destroy_empty_hopper";


	return "";
}
