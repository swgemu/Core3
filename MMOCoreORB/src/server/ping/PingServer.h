/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PINGSERVER_H_
#define PINGSERVER_H_

#include "PingClient.h"
#include "engine/service/DatagramServiceThread.h"
#include "engine/service/ServiceHandler.h"

namespace engine {
namespace service {
class Message;
class ServiceClient;
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

class PingServer : public DatagramServiceThread, public ServiceHandler {
public:
	PingServer();

	~PingServer();

	void initialize();

	void run();

	void shutdown();

	PingClient* createConnection(Socket* sock, SocketAddress& addr);

	void handleMessage(ServiceClient* client, Packet* message);

	void processMessage(Message* message);

	bool handleError(ServiceClient* client, Exception& e);

	void printInfo();

};

#endif /*PINGSERVERSERVER_H_*/
