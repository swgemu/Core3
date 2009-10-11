/*
 * LoginClient.h
 *
 *  Created on: Sep 4, 2009
 *      Author: theanswer
 */

#ifndef LOGINCLIENT_H_
#define LOGINCLIENT_H_

#include "engine/engine.h"

class LoginSession;

class LoginClient : public BaseClient {
	MessageQueue messageQueue;

	BasePacketHandler* basePacketHandler;
	LoginSession* loginSession;

public:
	LoginClient(int port);

	~LoginClient();

	void setLoginSession(LoginSession* session) {
		loginSession = session;
	}

	void handleMessage(Packet* message);

	Message* getMessage() {
		return messageQueue.pop();
	}

	void sendMessage(Message* msg) {
		BaseClient::sendPacket((BasePacket*) msg);
	}

	void sendMessage(StandaloneBaseMessage* msg) {
		BaseClient::sendPacket((BasePacket*) msg);
	}

	LoginSession* getLoginSession() {
		return loginSession;
	}

};


#endif /* LOGINCLIENT_H_ */
