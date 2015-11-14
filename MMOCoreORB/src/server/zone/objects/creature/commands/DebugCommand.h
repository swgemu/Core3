/*
 * DebugCommand.h
 *
 *  Created on: Apr 6, 2012
 *      Author: Kyle
 */

#ifndef DEBUGCOMMAND_H_
#define DEBUGCOMMAND_H_

#include "engine/engine.h"

class DebugCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->isPlayerCreature())
			return 1;

		StringTokenizer args(arguments.toString());

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL) {
			return 0;
		}

		try {

			String status;
			args.getStringToken(status);

			if(status.toLowerCase() == "on") {
				ghost->setDebug(true);
				creature->sendSystemMessage("Debug Output ON");
			} else {
				ghost->setDebug(false);
				creature->sendSystemMessage("Debug Output OFF");
			}

		} catch (Exception& e) {
			creature->sendSystemMessage(
					"SYNTAX: /server debug <on|off>");

			return 0;
		}
		return 0;
	}

};

#endif /* DEBUGCOMMAND_H_ */
