/*
 * GetMapLocationsCallback.h
 *
 *  Created on: 18/06/2010
 *      Author: victor
 */

#ifndef GETMAPLOCATIONSCALLBACK_H_
#define GETMAPLOCATIONSCALLBACK_H_

#include "server/zone/packets/MessageCallback.h"
#include "server/zone/Zone.h"

class GetMapLocationsCallback : public MessageCallback {
	String zoneName;

public:
	GetMapLocationsCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		message->parseAscii(zoneName);
	}

	void run() {
		ManagedReference<CreatureObject*> object = client->getPlayer();

		if (object == NULL)
			return;

		Locker _locker(object);

		Zone* zone = server->getZoneServer()->getZone(zoneName);

		if (zone != NULL)
			zone->sendMapLocationsTo(object);
	}
};

#endif /* GETMAPLOCATIONSCALLBACK_H_ */
