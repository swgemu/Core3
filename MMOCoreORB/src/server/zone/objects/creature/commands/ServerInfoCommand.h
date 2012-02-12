/*
 * ServerInfoCommand.h
 *
 *  Created on: 31/03/2011
 *      Author: xyborn
 */

#ifndef SERVERINFOCOMMAND_H_
#define SERVERINFOCOMMAND_H_

#include "engine/engine.h"
#include "server/zone/ZoneServer.h"

class ServerInfoCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return 1;

		ZoneServer* zserv = creature->getZoneServer();

		SuiMessageBox* box = new SuiMessageBox(creature, 0);
		box->setPromptTitle("Server Information");
		box->setPromptText(zserv->printInfo());

		ghost->addSuiBox(box);
		creature->sendMessage(box->generateMessage());

		return 0;
	}

	static void sendSyntax(CreatureObject* player) {
		if (player != NULL)
			player->sendSystemMessage("Syntax: /server info");
	}
};

#endif /* SERVERINFOCOMMAND_H_ */
