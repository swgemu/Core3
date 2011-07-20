/*
 * ObjectMenuSelect.h
 *
 *  Created on: 12/08/2009
 *      Author: victor
 */

#ifndef OBJECTMENUSELECT_H_
#define OBJECTMENUSELECT_H_

#include "../MessageCallback.h"

class ObjectMenuSelectCallback : public MessageCallback {
	uint64 objectID;
	uint8 radialID;
public:
	ObjectMenuSelectCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		objectID = message->parseLong();
		radialID = message->parseByte();
	}

	void run() {
		ManagedReference<CreatureObject*> player = (CreatureObject*)client->getPlayer();

		if (player != NULL) {
			RadialManager* radialManager = server->getZoneServer()->getRadialManager();
			radialManager->handleObjectMenuSelect(player, radialID, objectID);
		}
	}
};

#endif /* OBJECTMENUSELECT_H_ */
