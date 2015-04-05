/*
 * DefaultDroidAttackCommand.h
 *
 *  Created on: Jan 14, 2013
 *      Author: root
 */

#ifndef DEFAULTDROIDATTACKCOMMAND_H_
#define DEFAULTDROIDATTACKCOMMAND_H_
#include "CombatQueueCommand.h"

class DefaultDroidAttackCommand : public CombatQueueCommand {
public:

	DefaultDroidAttackCommand(const String& name, ZoneProcessServer* server)
		: CombatQueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return doCombatAction(creature, target);
	}

};





#endif /* DEFAULTDROIDATTACKCOMMAND_H_ */
