/*
 * ForcePowersQueueCommand.h
 *
 *  Created on: 24/05/2010
 *      Author: Valkyra
 */

#ifndef FORCEPOWERSQUEUECOMMAND_H_
#define FORCEPOWERSQUEUECOMMAND_H_

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

class ForcePowersQueueCommand : public CombatQueueCommand {
public:

	ForcePowersQueueCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {}

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

			ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

			if (playerObject != NULL && playerObject->getForcePower() <= forceCost) {
				creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.

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

				if (playerObject != NULL)
					playerObject->setForcePower(playerObject->getForcePower() - forceCost);

			} catch (Exception& e) {
				error("unreported exception caught in ForcePowersQueueCommand::doCombatAction");
				error(e.getMessage());
				e.printStackTrace();
			}
			// Increase Visibility for Force Power.
			VisibilityManager::instance()->increaseVisibility(creature);
			return SUCCESS;
		}

	float getCommandDuration(CreatureObject *object, const UnicodeString& arguments) {
		return defaultTime * speed;
	}

};

#endif /* FORCEPOWERSQUEUECOMMAND_H_ */
