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

#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/Zone.h"
#include "GetMapLocationsResponseMessage.h"

class GetMapLocationsCallback : public MessageCallback {
	String terrainName;

public:
	GetMapLocationsCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		message->parseAscii(terrainName);
	}

	void run() {
		PlayerCreature* object = (PlayerCreature*) client->getPlayer();

		if (object == NULL)
			return;

		Locker _locker(object);

		Zone* zone = server->getZoneServer()->getZone(terrainName);

		if (zone != NULL)
			zone->sendMapLocationsTo(object);
	}
};

#endif /* GETMAPLOCATIONSCALLBACK_H_ */
