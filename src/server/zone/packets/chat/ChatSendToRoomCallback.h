/*
 * ChatSendToRoomCallback.h
 *
 *  Created on: 30/12/2009
 *      Author: victor
 */

#ifndef CHATSENDTOROOMCALLBACK_H_
#define CHATSENDTOROOMCALLBACK_H_

#include "../MessageCallback.h"

class ChatSendToRoomCallback : public MessageCallback {
	UnicodeString message;
	uint32 roomID;
	uint32 counter;

public:
	ChatSendToRoomCallback(ZoneClientSession* client, ZoneProcessServerImplementation* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {

	}

	void run() {

	}

};


#endif /* CHATSENDTOROOMCALLBACK_H_ */
