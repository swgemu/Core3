/*
 * HarvesterObjectImplementation.cpp
 *
 *  Created on: 10/06/2010
 *      Author: victor
 */

#include "server/zone/objects/installation/harvester/HarvesterObject.h"
#include "server/zone/packets/harvester/HarvesterObjectMessage7.h"
#include "server/zone/objects/resource/ResourceContainer.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/harvester/ResourceHarvesterActivatePageMessage.h"

void HarvesterObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (!isOnAdminList(player))
		return;

	InstallationObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	menuResponse->addRadialMenuItemToRadialID(118, 78, 3, "@harvester:manage"); //Operate Machinery
}

void HarvesterObjectImplementation::synchronizedUIListen(CreatureObject* player, int value) {
	if (!player->isPlayerCreature() || !isOnAdminList(player) || getZone() == NULL)
		return;

	addOperator(player);

	updateInstallationWork();

	HarvesterObjectMessage7* msg = new HarvesterObjectMessage7(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(msg);

	/// Have to send the spawns of items no in shift, or the dont show
	/// up in the hopper when you look.
	for (int i = 0; i < resourceHopper.size(); ++i) {
		ResourceContainer* container = resourceHopper.get(i);

		if (container != NULL) {
			container->sendTo(player, true);
		}
	}

	activateUiSync();
}

void HarvesterObjectImplementation::updateOperators() {
	HarvesterObjectMessage7* msg = new HarvesterObjectMessage7(_this.getReferenceUnsafeStaticCast());
	broadcastToOperators(msg);
}

void HarvesterObjectImplementation::synchronizedUIStopListen(CreatureObject* player, int value) {
	if (!player->isPlayerCreature())
		return;

	removeOperator(player);
}

int HarvesterObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (!isOnAdminList(player))
		return 1;

	switch (selectedID) {
	case 78: {
		ResourceHarvesterActivatePageMessage* rhapm = new ResourceHarvesterActivatePageMessage(getObjectID());
		player->sendMessage(rhapm);
		break;
	}
	case 77:
		handleStructureAddEnergy(player);
		break;

	default:
		return InstallationObjectImplementation::handleObjectMenuSelect(player, selectedID);
	}

	return 0;
}

String HarvesterObjectImplementation::getRedeedMessage() {

	if(operating)
		return "destroy_deactivate_first";

	if(getHopperSize() > 0)
		return "destroy_empty_hopper";

	return "";
}


void HarvesterObjectImplementation::fillAttributeList(AttributeListMessage* alm,
		CreatureObject* object) {
	InstallationObjectImplementation::fillAttributeList(alm, object);

	if(isSelfPowered()){
		alm->insertAttribute("@veteran_new:harvester_examine_title", "@veteran_new:harvester_examine_text");
	}

}
