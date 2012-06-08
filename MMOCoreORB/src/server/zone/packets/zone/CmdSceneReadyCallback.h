/*
 * CmdSceneReadyCallback.h
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#ifndef CMDSCENEREADYCALLBACK_H_
#define CMDSCENEREADYCALLBACK_H_

#include "../MessageCallback.h"
#include "server/zone/objects/scene/SceneObject.h"

#include "CmdSceneReady.h"

class CmdSceneReadyCallback : public MessageCallback {
public:
	CmdSceneReadyCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {

	}

	void run() {
		ManagedReference<CreatureObject*> object = cast<CreatureObject*>( client->getPlayer().get().get());

		if (object == NULL)
			return;

		Locker _locker(object);

		PlayerObject* ghost = object->getPlayerObject();

		ghost->notifySceneReady();
	}
};



#endif /* CMDSCENEREADYCALLBACK_H_ */
