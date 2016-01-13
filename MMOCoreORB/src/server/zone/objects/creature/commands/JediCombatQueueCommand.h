/*
 * JediCombatQueueCommand.h
 *
 *  Created on: 1/11/2016
 *      Author: Greg Slomin
 */

#ifndef JEDICOMBATQUEUECOMMAND_H_
#define JEDICOMBATQUEUECOMMAND_H_

#include "CombatQueueCommand.h"

class JediCombatQueueCommand : public CombatQueueCommand {

public:

	JediCombatQueueCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
		visMod = 25;
	}

	virtual bool isJediCombatCommand() {
		return true;
	}
};

#endif /* JEDICOMBATQUEUECOMMAND_H_ */
