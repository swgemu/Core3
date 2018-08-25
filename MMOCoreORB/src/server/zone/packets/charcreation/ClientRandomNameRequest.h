/*
 * ClientRandomNameRequest.h
 *
 *  Created on: 22/07/2009
 *      Author: TheAnswer
 */

#ifndef CLIENTRANDOMNAMEREQUEST_H_
#define CLIENTRANDOMNAMEREQUEST_H_

#include "server/zone/packets/MessageCallback.h"
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

		int species = CreatureObject::HUMAN;

		if (raceFile.indexOf("wookiee") != -1)
			species = CreatureObject::WOOKIE;
		else if (raceFile.indexOf("bothan") != -1)
			species = CreatureObject::BOTHAN;
		else if (raceFile.indexOf("ithorian") != -1)
			species = CreatureObject::ITHORIAN;
		else if (raceFile.indexOf("moncal") != -1)
			species = CreatureObject::MONCAL;
		else if (raceFile.indexOf("rodian") != -1)
			species = CreatureObject::RODIAN;
		else if (raceFile.indexOf("sullustan") != -1)
			species = CreatureObject::SULLUSTAN;
		else if (raceFile.indexOf("trandoshan") != -1)
			species = CreatureObject::TRANDOSHAN;
		else if (raceFile.indexOf("twilek") != -1)
			species = CreatureObject::TWILEK;
		else if (raceFile.indexOf("zabrak") != -1)
			species = CreatureObject::ZABRAK;

		PlayerManager *playerManager = server->getPlayerManager();
		String name;
		int limiter = 0;
		do {
			name = nameManager->makeCreatureName(1, species);
		} while (playerManager->existsName(name) && ++limiter < 20);

		BaseMessage* msg = new ClientRandomNameResponse(raceFile, name);
		client->sendMessage(msg);
	}
};


#endif /* CLIENTRANDOMNAMEREQUEST_H_ */
