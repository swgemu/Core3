/*
 * CombatManager.h
 *
 *  Created on: 21/01/2010
 *      Author: victor
 */

#ifndef COMBATMANAGER_H_
#define COMBATMANAGER_H_

#include "engine/engine.h"
#include "server/zone/objects/creature/CreatureObject.h"

class CombatManager : public Singleton<CombatManager>, public Logger {


public:
	CombatManager() {
		setLoggingName("CombatManager");
		setGlobalLogging(true);
		setLogging(false);
	}

	/**
	 * Attempts combat between 2 creature objects
	 * @pre { attacker locked, defender unlocked }
	 * @post { attacker locked, defender unlocked }
	 * @param attacker attacking object
	 * @param defender defender object
	 * @return true on success
	 */
	bool startCombat(CreatureObject* attacker, TangibleObject* defender);

	/**
	 * Attempts to stop combat
	 * @pre { attacker locked }
	 * @post { attacker locked }
	 * @param attacker CreatureObject that attempts peace state
	 * @return true on succes
	 */
	bool attemptPeace(CreatureObject* attacker);

	/**
	 *
	 */

	//all the combat math will go here
};


#endif /* COMBATMANAGER_H_ */
