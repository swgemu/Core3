/*
 * GuildRequestCallback.h
 *
 *  Created on: Oct 29, 2010
 *      Author: crush
 */

#ifndef GUILDREQUESTCALLBACK_H_
#define GUILDREQUESTCALLBACK_H_

#include "../MessageCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "GuildResponseMessage.h"

class GuildRequestCallback : public MessageCallback {
	uint64 objectID;

public:
	GuildRequestCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		objectID = message->parseLong();
	}

	void run() {
		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(objectID);

		if (obj == NULL || !obj->isCreatureObject())
			return;

		CreatureObject* creature = cast<CreatureObject*>( obj.get());

		//ManagedReference<GuildObject*> guild = creature->getGuildObject();

		GuildResponseMessage* msg = new GuildResponseMessage(creature);
		client->sendMessage(msg);
	}
};

#endif /* GUILDREQUESTCALLBACK_H_ */
