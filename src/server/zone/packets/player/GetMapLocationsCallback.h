/*
 * GetMapLocationsCallback.h
 *
 *  Created on: 18/06/2010
 *      Author: victor
 */

#ifndef GETMAPLOCATIONSCALLBACK_H_
#define GETMAPLOCATIONSCALLBACK_H_


#include "../MessageCallback.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/terrain/PlanetNames.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/Zone.h"
#include "GetMapLocationsResponseMessage.h"

class GetMapLocationsCallback : public MessageCallback {
	String planet;

public:
	GetMapLocationsCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		message->parseAscii(planet);
	}

	void run() {
		PlayerCreature* object = (PlayerCreature*) client->getPlayer();

		if (object == NULL)
			return;

		Locker _locker(object);

		int id = Planet::getPlanetID(planet);

		if (id == -1)
			return;

		Zone* zone = server->getZoneServer()->getZone(id);

		if (zone != NULL) {
			zone->sendMapLocationsTo(planet, object);
		}
	}
};

#endif /* GETMAPLOCATIONSCALLBACK_H_ */
