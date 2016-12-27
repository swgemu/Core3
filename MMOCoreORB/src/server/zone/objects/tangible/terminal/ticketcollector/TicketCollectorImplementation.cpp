/*
 * TicketCollectorImplemetation.cpp
 *
 *  Created on: 30/05/2010
 *      Author: victor
 */

#include "server/zone/objects/tangible/terminal/ticketcollector/TicketCollector.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/jedi/JediManager.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/planet/PlanetTravelPoint.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/player/PlayerObject.h"

void TicketCollectorImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (JediManager::instance()->getJediProgressionType() == JediManager::VILLAGEJEDIPROGRESSION) {
		Zone* thisZone = getZone();

		if (thisZone == NULL)
			return;

		ManagedReference<PlanetManager*> pMan = thisZone->getPlanetManager();

		if (pMan == NULL)
			return;

		PlanetTravelPoint* ptp = pMan->getNearestPlanetTravelPoint(_this.getReferenceUnsafeStaticCast(), 64.f);

		if (ptp != NULL && ptp->isInterplanetary()) {
			PlayerObject* ghost = player->getPlayerObject();

			if (ghost != NULL && ghost->hasActiveQuestBitSet(PlayerQuestData::FS_CRAFTING4_QUEST_03) && !ghost->hasCompletedQuestsBitSet(PlayerQuestData::FS_CRAFTING4_QUEST_03))
				menuResponse->addRadialMenuItem(193, 3, "@quest/force_sensitive/fs_crafting:tracking_data_menu_obtain_data"); // Obtain Satellite Data
		}
	}
}

int TicketCollectorImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID == 20) {
		player->executeObjectControllerAction(0x5DCD41A2); //boardShuttle
	} else if (selectedID == 193 && JediManager::instance()->getJediProgressionType() == JediManager::VILLAGEJEDIPROGRESSION) {
		Zone* thisZone = getZone();

		if (thisZone == NULL)
			return 0;

		ManagedReference<PlanetManager*> planetManager = thisZone->getPlanetManager();

		if (planetManager == NULL)
			return 0;

		PlanetTravelPoint* ptp = planetManager->getNearestPlanetTravelPoint(_this.getReferenceUnsafeStaticCast(), 64.f);

		if (ptp != NULL && ptp->isInterplanetary()) {
			PlayerObject* ghost = player->getPlayerObject();

			if (ghost != NULL && ghost->hasActiveQuestBitSet(PlayerQuestData::FS_CRAFTING4_QUEST_03) && !ghost->hasCompletedQuestsBitSet(PlayerQuestData::FS_CRAFTING4_QUEST_03)) {
				Lua* lua = DirectorManager::instance()->getLuaInstance();
				Reference<LuaFunction*> luaObtainData = lua->createFunction("FsCrafting4", "obtainSatelliteData", 0);
				*luaObtainData << player;
				*luaObtainData << _this.getReferenceUnsafeStaticCast();

				luaObtainData->callFunction();
			}
		}
	}

	return 0;
}

