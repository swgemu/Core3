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
class LoginPacketHandler;

class LoginClient : public ServiceHandler {
	Reference<BaseClient*> client;

	MessageQueue messageQueue;

	BasePacketHandler* basePacketHandler;
	LoginSession* loginSession;
	LoginPacketHandler* loginPacketHandler;

public:
	LoginClient(int port, const String& loggingName);

	~LoginClient();

	void initialize();

	bool connect() {
		return client->connect();
	}

	void disconnect() {
		client->disconnect();
	}

	ServiceClient* createConnection(Socket* sock, SocketAddress& addr) {
		return NULL;
	}

	bool deleteConnection(ServiceClient* client) {
		return false;
	}

	void handleMessage(ServiceClient* client, Packet* message);

	void processMessage(Message* message);

	bool handleError(ServiceClient* client, Exception& e) {
		return true;
	}

	void setLoginSession(LoginSession* session) {
		loginSession = session;
	}

	void handleMessage(Packet* message);

	Message* getMessage() {
		return messageQueue.pop();
	}

	void sendMessage(Message* msg) {
		client->sendPacket((BasePacket*) msg);

	#ifdef WITH_STM
		TransactionalMemoryManager::commitPureTransaction();
	#endif
	}

	void sendMessage(StandaloneBaseMessage* msg) {
		client->sendPacket((BasePacket*) msg);
	}

	LoginSession* getLoginSession() {
		return loginSession;
	}

	BaseClient* getClient() {
		return client;
	}
};


#endif /* LOGINCLIENT_H_ */
