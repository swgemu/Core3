/*
 * ServerWhoCommand.h
 *
 *  Created on: Sat Jul  6 18:10:48 UTC 2019
 *      Author: lordkator
 */

#ifndef SERVERWHOCOMMAND_H_
#define SERVERWHOCOMMAND_H_

#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"

class ServerWhoCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (creature == nullptr)
			return 1;

		Reference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();

		int logSize = ConfigManager::instance()->getInt("Core3.OnlineLogSize", 100000000);

		playerManager->logOnlinePlayers(logSize);

		creature->sendSystemMessage("log/who.json updated.");

		return 0;
	}

	static void sendSyntax(CreatureObject* player) {
		if (player != NULL)
			player->sendSystemMessage("Syntax: /server who - Updates log/who.json and log/online-players.log");
	}
};

#endif /* SERVERWHOCOMMAND_H_ */
