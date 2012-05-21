/*
 * InsertPowerSuiCallback.h
 *
 *  Created on: may 22, 2012
 *      Author: kyle
 */

#ifndef INSERTPOWERSUICALLBACK_H_
#define INSERTPOWERSUICALLBACK_H_


#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/SuiBox.h"
#include "server/zone/managers/resource/ResourceManager.h"

class InsertPowerSuiCallback : public SuiCallback {
public:
	InsertPowerSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		if (!suiBox->isTransferBox() || cancelPressed != 0)
			return;

		if (args->size() < 1)
			return;

		uint32 newEnergyVal = (uint64) Long::valueOf(args->get(0).toString());

		ManagedReference<SceneObject*> object = suiBox->getUsingObject();

		if (object == NULL || !object->isInstallationObject())
			return;

		InstallationObject* installation = cast<InstallationObject*>( object.get());

		ManagedReference<ResourceManager*> resourceManager = player->getZoneServer()->getResourceManager();

		//TODO: This should be handled in StructureManager

		Locker _lock(installation, player);

		uint32 energyFromPlayer = resourceManager->getAvailablePowerFromPlayer(player);
		uint32 energy = energyFromPlayer - newEnergyVal;

		if (energy > energyFromPlayer)
			return;

		installation->addPower(energy);
		resourceManager->removePowerFromPlayer(player, energy);

		StringIdChatParameter stringId("player_structure", "deposit_successful");
		stringId.setDI(energy);

		player->sendSystemMessage(stringId);

		stringId.setStringId("player_structure", "reserve_report");
		stringId.setDI(installation->getSurplusPower());

		player->sendSystemMessage(stringId);

		installation->updateToDatabase();
	}

};

#endif /* INSERTPOWERSUICALLBACK_H_ */
