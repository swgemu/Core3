/*
 * CombatManager.cpp
 *
 *  Created on: 24/02/2010
 *      Author: victor
 */

#include "CombatManager.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "server/zone/objects/creature/CreatureState.h"

bool CombatManager::startCombat(CreatureObject* attacker, TangibleObject* defender) {
	defender->wlock(attacker);


	try {
		attacker->setDefender(defender);
		defender->setDefender(attacker);

		attacker->setCombatState();
		defender->setCombatState();
	} catch (...) {

	}

	defender->unlock();

	return true;
}

bool CombatManager::attemptPeace(CreatureObject* attacker) {
	DeltaVector<ManagedReference<SceneObject*> >* defenderList = attacker->getDefenderList();

	for (int i = 0; i < defenderList->size(); ++i) {
		ManagedReference<SceneObject*> object = defenderList->get(i);

		if (!object->isCreatureObject())
			continue;

		TangibleObject* defender = (TangibleObject*) object.get();

		try {
			defender->wlock(attacker);

			if (defender->hasDefender(attacker)) {

				if (defender->isCreatureObject()) {
					CreatureObject* creature = (CreatureObject*) defender;

					if (creature->hasState(CreatureState::PEACE)) {
						attacker->removeDefender(defender);
						defender->removeDefender(attacker);

						--i;
					}
				} else {
					attacker->removeDefender(defender);
					defender->removeDefender(attacker);

					--i;
				}
			} else {
				attacker->removeDefender(defender);
				--i;
			}

			defender->unlock();

		} catch (...) {
			error("unknown exception in PlayerImplementation::doPeace()\n");
			defender->unlock();
		}

	}

	if (defenderList->size() != 0) {
		//info("defenderList not empty, trying to set Peace State");

		attacker->setState(CreatureState::PEACE);

		return false;
	} else {
		return true;
	}
}
