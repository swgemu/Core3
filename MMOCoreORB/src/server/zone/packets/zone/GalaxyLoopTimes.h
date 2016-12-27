/*
 * RequestGalaxyLoopTimes.h
 *
 *  Created on: 15/08/2009
 *      Author: victor
 */

#ifndef REQUESTGALAXYLOOPTIMES_H_
#define REQUESTGALAXYLOOPTIMES_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/packets/MessageCallback.h"

class GalaxyLoopTimesResponse : public BaseMessage {
public:
	GalaxyLoopTimesResponse() : BaseMessage() {
		insertShort(3);
		insertInt(0x4E428088);
		insertInt(0);
		insertInt(0);
		insertInt(0);
	}
};

class RequestGalaxyLoopTimesCallback : public MessageCallback {
public:
	RequestGalaxyLoopTimesCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
	}

	void run() {
		// this makes the client spam the server with GalaxyLoopTimes requests
		// TODO: figure out the values in the Response

		/*GalaxyLoopTimesResponse* reply = new GalaxyLoopTimesResponse();
		client->sendMessage(reply);*/
	}
};

#endif
