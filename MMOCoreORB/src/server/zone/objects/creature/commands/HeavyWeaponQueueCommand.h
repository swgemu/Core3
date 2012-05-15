/*
 * HeavyWeaponQueueCommand.h
 *
 *  Created on: 13/05/2012
 *      Author: chris.rush
 */

#ifndef HEAVYWEAPONQUEUECOMMAND_H_
#define HEAVYWEAPONQUEUECOMMAND_H_

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

class HeavyWeaponQueueCommand : public CombatQueueCommand {
public:

	HeavyWeaponQueueCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
		damageMax = 0;
		accuracySkillMod = "";

		// Force Power is only set in Jedi-skills.
		forceCost = 0;
		speed = 0;

		damageMultiplier = 0;
		accuracyBonus = 0;
		speedMultiplier = 0;
		healthCostMultiplier = 0;
		actionCostMultiplier = 0;
		mindCostMultiplier = 0;

		// Force Power is only set in Jedi-skills.
		forceCostMultiplier = 0;

		poolsToDamage = CombatManager::RANDOM;

		knockdownStateChance = 0;
		postureDownStateChance = 0;
		postureUpStateChance = 0;
		dizzyStateChance = 0;
		blindStateChance = 0;
		stunStateChance = 0;
		intimidateStateChance = 0;
		nextAttackDelayChance = 0;

		durationStateTime = 10;

		dotDuration = 0;
		dotType = 0;
		dotPool = 0;
		dotStrength = 0;
		dotPotency = 0;

		coneAngle = 30;
		dotDamageOfHit = false;


		range = 1;

		areaRange = 0;
		areaAction = false;
		coneAction = false;

		combatSpam = "";
		animationCRC = 0;
	}

	int doCombatAction(CreatureObject* creature, const uint64& target, const UnicodeString& arguments = "") {
			ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);
			PlayerManager* playerManager = server->getPlayerManager();

			if (targetObject == NULL || !targetObject->isTangibleObject() || targetObject == creature)
				return INVALIDTARGET;

			float checkRange = range;

			if (creature->isProne())
				return NOPRONE;

			if (!targetObject->isInRange(creature, checkRange))
				return TOOFAR;

			if (!CollisionManager::checkLineOfSight(creature, targetObject)) {
				creature->sendSystemMessage("@container_error_message:container18");
				return GENERALERROR;
			}

			CombatManager* combatManager = CombatManager::instance();

			try {
				int res = combatManager->doCombatAction(creature, cast<TangibleObject*>(targetObject.get()), CreatureAttackData(arguments, this));

				switch (res) {
				case -1:
					return INVALIDTARGET;
				case -3:
					return GENERALERROR;
				}
			} catch (Exception& e) {
				error("unreported exception caught in HeavyWeaponQueueCommand::doCombatAction");
				error(e.getMessage());
				e.printStackTrace();
			}
			return SUCCESS;
		}

	float getCommandDuration(CreatureObject *object) {
		return defaultTime * speed;
	}

};

#endif /* HEAVYWEAPONQUEUECOMMAND_H_ */
