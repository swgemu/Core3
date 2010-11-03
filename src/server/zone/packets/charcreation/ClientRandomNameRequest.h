/*
 * ClientRandomNameRequest.h
 *
 *  Created on: 22/07/2009
 *      Author: TheAnswer
 */

#ifndef CLIENTRANDOMNAMEREQUEST_H_
#define CLIENTRANDOMNAMEREQUEST_H_

#include "../MessageCallback.h"
#include "ClientRandomNameResponse.h"

#include "server/zone/managers/name/NameManager.h"

class ClientRandomNameRequest : public MessageCallback {
	String raceFile;

public:
	ClientRandomNameRequest(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {
	}

	void parse(Message* message) {
		message->parseAscii(raceFile);
	}

	void run() {
		NameManager* nameManager = server->getNameManager();

		bool notwook = (raceFile.indexOf("wookie") == -1);

		BaseMessage* msg = new ClientRandomNameResponse(raceFile, nameManager->makeCreatureName(notwook));
		client->sendMessage(msg);
	}
};


#endif /* CLIENTRANDOMNAMEREQUEST_H_ */
