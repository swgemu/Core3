/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef PLAYERSNEARYOU_H_
#define PLAYERSNEARYOU_H_

#include "ObjectControllerMessage.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/planet/PlanetManager.h"

class PlayersNearYouMessage : public ObjectControllerMessage {
public:
	PlayersNearYouMessage(CreatureObject* creo) : ObjectControllerMessage(creo->getObjectID(), 0x0B, 0x1E7) {
		insertInt(0); // No players.
	}

	void addFoundPlayer(CreatureObject* player) {
		// Player Bitmasks
		PlayerObject* ghost = player->getPlayerObject();

		if (ghost != nullptr) {
			insertInt(0x04);

			const PlayerBitmasks* playerBits = ghost->getPlayerBitmasks();

			for (int i = 0; i < 4; ++i) {
				insertInt(playerBits->getBitmask(i));
			}
		}

		insertUnicode(player->getDisplayedName()); // Player name.

		uint32 race = player->getSpecies();

		insertInt(race); // Race ID

		String regionName = "";
		String zoneName = "";

		Zone* zone = player->getZone();

		if (zone != nullptr) {
			zoneName = zone->getZoneName();
		}

		if (player->getCityRegion() != nullptr) {
			CityRegion* cityRegion = player->getCityRegion().get();

			if (cityRegion != nullptr)
				regionName =  cityRegion->getCityRegionName();
		} else {
			SortedVector<ManagedReference<ActiveArea*> >* areas = player->getActiveAreas();

			for (int i = 0; i < areas->size(); i++) {
				ActiveArea* area = areas->get(i);

				if (area == nullptr || !area->isNamedRegion())
					continue;

				regionName = area->getAreaName();
				break;
			}
		}

		insertAscii(regionName); //Region Name
		insertAscii(zoneName); //Planet

		String guildName = "";

		if (player->isInGuild()) {
			ManagedReference<GuildObject*> guild = player->getGuildObject().get();
			guildName = guild->getGuildName();
		}

		insertAscii(guildName);

		String title = "";

		if (ghost != nullptr)
			title = ghost->getTitle();

		 // Profession Title
		insertAscii(title);
	}

	void insertPlayerCounter(uint32 foundCount) {
		insertInt(30, foundCount);
	}

};

#endif /*PLAYERSNEARYOU_H_*/
