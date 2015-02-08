/*
 * JediCombatQueueCommand.h
 *
 *  Created on: Dec 15, 2014
 *      Author: valkyra
 */

#ifndef JEDICOMBATQUEUECOMMAND_H_
#define JEDICOMBATQUEUECOMMAND_H_


#include "CombatQueueCommand.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/visibility/VisibilityManager.h"

class JediCombatQueueCommand : public CombatQueueCommand {
public:

	JediCombatQueueCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {}

	int doJediCombatAction(CreatureObject* creature, const uint64& target, const UnicodeString& arguments = "") {
		ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();
		ManagedReference<WeaponObject*> weapon = NULL;

		if (creature->getWeapon() != NULL)
			weapon = creature->getWeapon();


		if (!weapon->isJediWeapon()) {
			return INVALIDWEAPON;
		}

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		if (playerObject != NULL && playerObject->getForcePower() <= forceCost) {
			creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.

			return GENERALERROR;
		}


		int res = doCombatAction(creature, target, arguments, weapon);

		if (res != SUCCESS)
			return res;

		// Saber attacks are handled in the CombatManager...
		if (playerObject != NULL)
			playerObject->setForcePower(playerObject->getForcePower() - forceCost);

		// Increase Visibility for Force Power.
		VisibilityManager::instance()->increaseVisibility(creature);

		return SUCCESS;
	}

	float getCommandDuration(CreatureObject *object, const UnicodeString& arguments) {
		if (isForceAttack())
			return defaultTime * speed;
		else
			return CombatManager::instance()->calculateWeaponAttackSpeed(object, object->getWeapon(), speedMultiplier);
	}

	bool isForceAttack() {
		return !name.contains("saber");
	}

};


#endif /* JEDICOMBATQUEUECOMMAND_H_ */
