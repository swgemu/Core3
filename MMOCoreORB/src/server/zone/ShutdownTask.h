/*
 * ShutdownTask.h
 *
 *  Created on: 20/05/2012
 *      Author: victor
 */

#ifndef SHUTDOWNTASK_H_
#define SHUTDOWNTASK_H_

#include "engine/engine.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/ChatManager.h"

class ShutdownTask : public Task {
	int minutesRemaining;
	ManagedReference<ZoneServer*> zoneServer;
public:
	ShutdownTask(ZoneServer* srv, int minutes) {
		zoneServer = srv;
		minutesRemaining = minutes;
	}

	void run() {
		--minutesRemaining;

		String str = "Server will shutdown in " + String::valueOf(minutesRemaining) + " minutes";
		Logger::console.info(str, true);

		if (minutesRemaining == 0)
			str = "SHUTTING DOWN NOW!";

		zoneServer->getChatManager()->broadcastGalaxy(NULL, str);

		if (minutesRemaining == 0) {
			Logger::console.info("SHUTDOWN NOW!", true);
			ServerCore::getInstance()->signalShutdown();
		} else {
			schedule(60 * 1000);
		}

	}
};


#endif /* SHUTDOWNTASK_H_ */
