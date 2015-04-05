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

	HeavyWeaponQueueCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {}

	int doCombatAction(CreatureObject* creature, const uint64& target, const UnicodeString& arguments = "") const {
			ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);
			PlayerManager* playerManager = server->getPlayerManager();

			if (targetObject == NULL || !targetObject->isTangibleObject() || targetObject == creature)
				return INVALIDTARGET;

			float checkRange = range;

			if (creature->isProne())
				return NOPRONE;

			if (!targetObject->isInRange(creature, checkRange + targetObject->getTemplateRadius() + creature->getTemplateRadius()))
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

	float getCommandDuration(CreatureObject *object, const UnicodeString& arguments) const {
		return defaultTime * speed;
	}

};

#endif /* HEAVYWEAPONQUEUECOMMAND_H_ */
