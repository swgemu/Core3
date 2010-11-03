/*
 * StatusHandler.h
 *
 *  Created on: Oct 5, 2010
 *      Author: oru
 */

#ifndef STATUSHANDLER_H_
#define STATUSHANDLER_H_

#include "StatusServer.h"



class StatusHandler: public ServiceHandler {
	StatusServer* statusServerRef;

public:
	StatusHandler(StatusServer* server) {
		statusServerRef = server;
	}

	void initialize() {

	}

	ServiceClient* createConnection(Socket* sock, SocketAddress& addr) {
		return statusServerRef->createConnection(sock, addr);
	}

	bool deleteConnection(ServiceClient* client) {
		return false;
	}

	void handleMessage(ServiceClient* client, Packet* message) {

	}

	void processMessage(Message* message) {

	}

	bool handleError(ServiceClient* client, Exception& e) {
		return false;
	}

};


using namespace server::zone;


#endif /* STATUSHANDLER_H_ */
