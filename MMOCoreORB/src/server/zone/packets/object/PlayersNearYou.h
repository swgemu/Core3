/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
 */

#ifndef PLAYERSNEARYOU_H_
#define PLAYERSNEARYOU_H_

#include "ObjectControllerMessage.h"

#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

#include "server/zone/managers/planet/PlanetManager.h"

#include "server/zone/objects/player/Races.h"

#include "server/zone/objects/terrain/RegionNames.h"

class PlayersNearYouMessage : public ObjectControllerMessage {
public:
	PlayersNearYouMessage(CreatureObject* creo) 
: ObjectControllerMessage(creo->getObjectID(), 0x0B, 0x1E7) {
		insertInt(0); // No players.
	}

	void addFoundPlayer(CreatureObject* player) {
		// Bitmask.
		PlayerObject* ghost = player->getPlayerObject();

		uint32 playerBitmask = 0;

		if (ghost != NULL)
			playerBitmask = ghost->getCharacterBitmask();

		insertInt(1);
		insertInt(playerBitmask); // Flags bitmask.

		insertUnicode(player->getDisplayedName()); // Player name.

		uint32 race = player->getSpecies();

		insertInt(race); // Race ID

		String regionName = "";
		String zoneName = "";

		Zone* zone = player->getZone();

		if (zone != NULL) {
			zoneName = zone->getZoneName();

			PlanetManager* planetManager = zone->getPlanetManager();
			CityRegion* cityRegion = planetManager->getRegionAt(player->getWorldPositionX(), player->getWorldPositionY());

			if (cityRegion != NULL)
				regionName = cityRegion->getRegionName();
		}

		insertAscii(regionName); //Region Name
		insertAscii(zoneName); //Planet

		String guildName = "";

		if (player->isInGuild())
			guildName = player->getGuildObject()->getGuildName();

		insertAscii(guildName);

		String title = "";

		if (ghost != NULL)
			title = ghost->getTitle();

		insertAscii(title); // Profession Title
	}

	void insertPlayerCounter(uint32 foundCount) {
		insertInt(30, foundCount);
	}

};

#endif /*PLAYERSNEARYOU_H_*/
