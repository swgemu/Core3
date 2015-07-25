/*
 * ForcePowersQueueCommand.h
 *
 *  Created on: 24/05/2010
 *      Author: Valkyra
 */

#ifndef FORCEPOWERSQUEUECOMMAND_H_
#define FORCEPOWERSQUEUECOMMAND_H_


#include "CombatQueueCommand.h"

#include "server/zone/managers/visibility/VisibilityManager.h"

class ForcePowersQueueCommand : public CombatQueueCommand {
protected:
	float damageMin;
	float damageMax;
public:
	ForcePowersQueueCommand(const String& name, ZoneProcessServer* server) : CombatQueueCommand(name, server) {
		damageMin = 0;
		damageMax = 0;
	}

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

			ManagedReference<PlayerObject*> playerObject = creature->getPlayerObject();

			if (playerObject != NULL && playerObject->getForcePower() <= forceCost) {
				creature->sendSystemMessage("@jedi_spam:no_force_power"); //"You do not have enough Force Power to peform that action.

				return GENERALERROR;
			}

			CombatManager* combatManager = CombatManager::instance();
			UnicodeString args = "";

			try {
				int res = combatManager->doCombatAction(creature, creature->getWeapon(), cast<TangibleObject*>(targetObject.get()), CreatureAttackData(arguments, this));

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

	float getCommandDuration(CreatureObject *object, const UnicodeString& arguments) const {
		return speed;
	}

	bool isForcePowersCommand() {
		return true;
	}

	void setDamageMin(float dmgmin) {
		damageMin = dmgmin;
	}

	void setDamageMax(float dmgmx) {
		damageMax = dmgmx;
	}

	inline float getDamageMin() const {
		return damageMin;
	}

	inline float getDamageMax() const {
		return damageMax;
	}

};

#endif /* FORCEPOWERSQUEUECOMMAND_H_ */
