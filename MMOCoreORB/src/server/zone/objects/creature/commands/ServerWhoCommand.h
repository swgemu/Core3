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
#include "server/zone/objects/player/events/OnlinePlayerLogTask.h"

class ServerWhoCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (creature == nullptr)
			return 1;

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return 1;

		Reference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

		if (playerManager == nullptr)
			return 1;

		StringTokenizer tokenizer(arguments.toString());

		if (tokenizer.hasMoreTokens()) {
			try {
				int logSeconds = tokenizer.getIntToken();

				if (playerManager->rescheduleOnlinePlayerLogTask(logSeconds)) {
					String msg;

					if (logSeconds > 0)
						msg = "changed online log updates to every " + String::valueOf(logSeconds) + " seconds.";
					else
						msg = "disabled online log updates.";

					creature->info(msg, true);
					creature->sendSystemMessage(msg);
				} else {
					creature->sendSystemMessage("Failed to change online log period to " + String::valueOf(logSeconds) + " second(s), might be too low.");
				}
			} catch (Exception& e) {
				creature->error("Exception trying to change OnlinePlayerLogTask schedule: " + e.getMessage());
			}

			return 0;
		}

		playerManager->logOnlinePlayers(true);

		creature->sendSystemMessage("log/who.json updated.");

		return 0;
	}

	static void sendSyntax(CreatureObject* player) {
		if (player != nullptr)
			player->sendSystemMessage("Syntax: /server who - Updates log/who.json and log/online-players.log");
	}
};

#endif /* SERVERWHOCOMMAND_H_ */
