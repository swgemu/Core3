/*
 * PlanetTravelPointListRequestCallback.h
 *
 *  Created on: 31/05/2010
 *      Author: victor
 */

#ifndef PLANETTRAVELPOINTLISTREQUESTCALLBACK_H_
#define PLANETTRAVELPOINTLISTREQUESTCALLBACK_H_


#include "../MessageCallback.h"

#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/Zone.h"

class PlanetTravelPointListRequestCallback : public MessageCallback {
	uint64 objectid;
	String zoneName;
public:
	PlanetTravelPointListRequestCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		objectid = message->parseLong();
		message->parseAscii(zoneName);
	}

	void run() {
		PlayerCreature* object = (PlayerCreature*) client->getPlayer();

		if (object == NULL)
			return;

		Locker _locker(object);

		Zone* zone = server->getZoneServer()->getZone(zoneName);

		if (zone == NULL)
			return;

		PlanetManager* planetManager = zone->getPlanetManager();
		planetManager->sendPlanetTravelPointListResponse(object);
	}
};


#endif /* PLANETTRAVELPOINTLISTREQUESTCALLBACK_H_ */
