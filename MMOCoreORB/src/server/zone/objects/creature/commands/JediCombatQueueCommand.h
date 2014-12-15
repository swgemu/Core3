/*
 * JediCombatQueueCommand.h
 *
 *  Created on: Dec 15, 2014
 *      Author: valkyra
 */

#ifndef JEDICOMBATQUEUECOMMAND_H_
#define JEDICOMBATQUEUECOMMAND_H_


#include"server/zone/ZoneServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/combat/CreatureAttackData.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/objects/creature/CreatureState.h"
#include "server/zone/objects/creature/commands/effect/StateEffect.h"
#include "server/zone/objects/creature/commands/effect/DotEffect.h"
#include "server/zone/objects/creature/commands/effect/CommandEffect.h"
#include "CombatQueueCommand.h"
#include "server/zone/managers/collision/PathFinderManager.h"
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
