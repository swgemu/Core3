/*
 * PlanetTravelPointListRequestCallback.h
 *
 *  Created on: 31/05/2010
 *      Author: victor
 */

#ifndef PLANETTRAVELPOINTLISTREQUESTCALLBACK_H_
#define PLANETTRAVELPOINTLISTREQUESTCALLBACK_H_


#include "../MessageCallback.h"
#include "server/zone/objects/terrain/PlanetNames.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/Zone.h"

class PlanetTravelPointListRequestCallback : public MessageCallback {
	uint64 objectid;
	String planet;

public:
	PlanetTravelPointListRequestCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		objectid = message->parseLong();
		message->parseAscii(planet);
	}

	void run() {
		PlayerCreature* object = (PlayerCreature*) client->getPlayer();

		if (object == NULL)
			return;

		Locker _locker(object);

		int id = Planet::getPlanetID(planet);

		Zone* zone = server->getZoneServer()->getZone(id);

		if (zone != NULL) {
			PlanetManager* planetManager = zone->getPlanetManager();

			planetManager->sendPlanetTravelPointListResponse(object);
		}
	}
};


#endif /* PLANETTRAVELPOINTLISTREQUESTCALLBACK_H_ */
