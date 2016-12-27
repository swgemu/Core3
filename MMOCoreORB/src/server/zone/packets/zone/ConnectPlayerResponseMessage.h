/*
 * ConnectPlayerResponseMessage.h
 *
 *  Created on: Nov 25, 2008
 *      Author: swgemu
 */

#ifndef CONNECTPLAYERRESPONSEMESSAGE_H_
#define CONNECTPLAYERRESPONSEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/packets/MessageCallback.h"

class ConnectPlayerResponseMessage : public BaseMessage {
public:
   ConnectPlayerResponseMessage() : BaseMessage() {
		    insertShort(0x02);
	   		insertInt(0x6137556F);

	   		insertInt(0);
   }

};

class ConnectPlayerMessageCallback : public MessageCallback {
public:
	ConnectPlayerMessageCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
	}

	void run() {
		ConnectPlayerResponseMessage* cprm = new ConnectPlayerResponseMessage();
		client->sendMessage(cprm);
	}
};


#endif /* CONNECTPLAYERRESPONSEMESSAGE_H_ */
