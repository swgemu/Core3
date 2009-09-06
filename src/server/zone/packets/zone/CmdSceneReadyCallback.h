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
	CmdSceneReadyCallback(ZoneClientSession* client, ZoneProcessServerImplementation* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {

	}

	void run() {
		BaseMessage* msg = new CmdSceneReady();
		client->sendMessage(msg);
	}
};



#endif /* CMDSCENEREADYCALLBACK_H_ */
