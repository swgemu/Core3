/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PINGSERVER_H_
#define PINGSERVER_H_

#include "engine/engine.h"

#include "PingClient.h"

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
