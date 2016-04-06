/*
 * RevisionInfoCommand.h
 *
 *  Created on: 01/13, 2012
 *      Author: Elvaron
 */

#ifndef REVISIONINFOCOMMAND_H_
#define REVISIONINFOCOMMAND_H_

#include "engine/engine.h"
#include "conf/ConfigManager.h"

class RevisionInfoCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->isPlayerCreature())
			return 1;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);
		ConfigManager* configManager = ConfigManager::instance();

		player->sendSystemMessage("Server Information");
		player->sendSystemMessage(configManager->getRevision());

		return 0;
	}

};

#endif /* REVISIONINFOCOMMAND_H_ */
