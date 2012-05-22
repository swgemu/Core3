/*
 * LagReport.h
 *
 *  Created on: 15/08/2009
 *      Author: victor
 */

#ifndef LAGREPORT_H_
#define LAGREPORT_H_

#include "../MessageCallback.h"

class GameServerLagResponse : public BaseMessage {
public:
	GameServerLagResponse() : BaseMessage() {
		insertShort(1); // figure out
		insertInt(0x789A4E0A);

	}
};

class ConnectionServerLagResponse : public BaseMessage {
public:
	ConnectionServerLagResponse() : BaseMessage() {
		insertShort(1); // figure out
		insertInt(0x1590F63C);

	}
};

class LagReportCallback : public MessageCallback {
	uint64 unknown;
public:
	LagReportCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		unknown = message->parseLong();
	}

	void run() {
	}
};

class LagRequestCallback : public MessageCallback {
public:
	LagRequestCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
	}

	void run() {
		ManagedReference<ZoneClientSession*> session = client.get();

		if (session == NULL)
			return;

		ConnectionServerLagResponse* connectionServer = new ConnectionServerLagResponse();
		session->sendMessage(connectionServer);

		GameServerLagResponse* gameServer = new GameServerLagResponse();
		session->sendMessage(gameServer);
	}
};

#endif /* LAGREPORT_H_ */
