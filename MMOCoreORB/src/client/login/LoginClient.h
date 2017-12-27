/*
 * LoginClient.h
 *
 *  Created on: Sep 4, 2009
 *      Author: theanswer
 */

#ifndef LOGINCLIENT_H_
#define LOGINCLIENT_H_

#include <stddef.h>

#include "engine/engine.h"
#include "engine/service/MessageQueue.h"
#include "engine/service/ServiceHandler.h"
#include "engine/service/proto/BaseClient.h"
#include "engine/service/proto/BasePacket.h"
#include "engine/service/proto/StandaloneBaseMessage.h"
#include "login/LoginSession.h"
#include "system/lang/String.h"
#include "system/lang/ref/Reference.h"

class LoginPacketHandler;
class LoginSession;
namespace engine {
namespace service {
class Message;
class ServiceClient;
namespace proto {
class BasePacketHandler;
}  // namespace proto
}  // namespace service
}  // namespace engine
namespace sys {
namespace lang {
class Exception;
}  // namespace lang
namespace net {
class Packet;
class Socket;
class SocketAddress;
}  // namespace net
}  // namespace sys

class LoginClient : public ServiceHandler {
	Reference<BaseClient*> client;

	MessageQueue messageQueue;

	BasePacketHandler* basePacketHandler;
	Reference<LoginSession*> loginSession;
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
		//TransactionalMemoryManager::commitPureTransaction();
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
