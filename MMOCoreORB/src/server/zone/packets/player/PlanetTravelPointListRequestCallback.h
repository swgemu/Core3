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
#include "PlanetTravelPointListResponse.h"
#include "server/zone/Zone.h"

class PlanetTravelPointListRequestCallback : public MessageCallback {
	String zoneName;

public:
	PlanetTravelPointListRequestCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		message->shiftOffset(8); //We don't need the player object, we got it already.
		message->parseAscii(zoneName);
	}

	void run() {
		CreatureObject* object = cast<CreatureObject*>( client->getPlayer().get().get());

		if (object == NULL)
			return;

		Locker _locker(object);

		Zone* zone = server->getZoneServer()->getZone(zoneName);

		//Handles unknown or disabled zones.
		if (zone == NULL) {
			object->info("Attempting to travel to non-existant, or disabled, zone [" + zoneName + "].");

			PlanetTravelPointListResponse* ptplr = new PlanetTravelPointListResponse(zoneName);
			ptplr->addPoint("", 0, 0, 0, 0, 0);
			ptplr->generateMessage();
			object->sendMessage(ptplr);

			return;
		}

		PlanetManager* planetManager = zone->getPlanetManager();
		planetManager->sendPlanetTravelPointListResponse(object);
	}
};


#endif /* PLANETTRAVELPOINTLISTREQUESTCALLBACK_H_ */
