
#ifndef SURRENDERPILOTSUICALLBACK_H_
#define SURRENDERPILOTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "templates/faction/Factions.h"

class SurrenderPilotSuiCallback : public SuiCallback {
	uint32 faction;

public:
	SurrenderPilotSuiCallback(ZoneServer* server, uint32 factionHash) : SuiCallback(server) {
		faction = factionHash;
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		if (eventIndex != 1 || player == nullptr) {
			return;
		}

		auto ghost = player->getPlayerObject();

		if (ghost == nullptr) {
			return;
		}

		ManagedReference<WaypointObject*> waypoint = (server->createObject(0xc456e788, 1)).castTo<WaypointObject*>();

		if (waypoint == nullptr) {
			return;
		}

		Locker locker(waypoint, player);

		if (faction == Factions::FACTIONREBEL) {
			waypoint->setCustomObjectName("@npc_spawner_n:j_pai_brek", false);

			waypoint->setPlanetCRC(STRING_HASHCODE("corellia"));

			waypoint->setPosition(-5072, 0, -2343);

			waypoint->setColor(WaypointObject::COLOR_BLUE);
		} else if (faction == Factions::FACTIONIMPERIAL) {
			waypoint->setCustomObjectName("@npc_spawner_n:landau", false);

			waypoint->setPlanetCRC(STRING_HASHCODE("naboo"));

			waypoint->setPosition(-5516, 0, 4403);

			waypoint->setColor(WaypointObject::COLOR_BLUE);
		} else {
			waypoint->setCustomObjectName("@npc_spawner_n:gil_burtin", false);

			waypoint->setPlanetCRC(STRING_HASHCODE("tatooine"));

			waypoint->setPosition(-1174, 0, -3674);

			waypoint->setColor(WaypointObject::COLOR_BLUE);
		}

		waypoint->setActive(true);

		ghost->addWaypoint(waypoint, false, true);
	}
};

#endif /* SURRENDERPILOTSUICALLBACK_H_ */
