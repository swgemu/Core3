/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef REVIVETARGETSKILL_H_
#define REVIVETARGETSKILL_H_

#include "../TargetSkill.h"
#include "../../../tangible/pharmaceutical/PharmaceuticalImplementation.h"
#include "../../../tangible/pharmaceutical/RevivePackImplementation.h"

#include "../../../../managers/player/PlayerManager.h"

class ReviveTargetSkill : public TargetSkill {
protected:
	String effectName;
	int mindCost;

public:
	ReviveTargetSkill(const String& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, REVIVE, serv) {
		effectName = aname;
		mindCost = 0;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!effectName.isEmpty())
			creatureTarget->playEffect(effectName, "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	bool canPerformSkill(CreatureObject* creature, Player* playerTarget, RevivePack* revivePack) {
		if (!playerTarget->isDead()) {
			creature->sendSystemMessage("healing_response", "healing_response_a4"); //Your target does not require resuscitation!
			return 0;
		}

		if (revivePack == NULL) {
			creature->sendSystemMessage("healing_response", "cannot_resuscitate_kit"); //You cannot resuscitate someone without a resuscitation kit!
			return false;
		}

		if (!playerTarget->isResurrectable()) {
			creature->sendSystemMessage("healing_response", "too_dead_to_resuscitate"); //Your target has been dead too long. There is no hope of resuscitation.
			return false;
		}

		if (creature->isProne()) {
			creature->sendSystemMessage("You cannot Revive while prone.");
			return false;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot Revive while Meditating.");
			return false;
		}

		if (creature->isRidingCreature()) {
			creature->sendSystemMessage("You cannot do that while Riding a Creature.");
			return false;
		}

		if (creature->isMounted()) {
			creature->sendSystemMessage("You cannot do that while Driving a Vehicle.");
			return false;
		}

		if (playerTarget->isOvert() && playerTarget->getFaction() != creature->getFaction()) {
			creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
			return false;
		}

		if (!creature->isInGroupWith((CreatureObject*) playerTarget) && !((Player*)creature)->hasConsentFrom(playerTarget)) {
			creature->sendSystemMessage("healing_response", "must_be_grouped"); //You must be grouped with or have consent from your resuscitation target!
			return false;
		}

		if (creature->getMind() < abs(mindCost)) {
			creature->sendSystemMessage("healing_response", "not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		return true;
	}

	void parseModifier(const String& modifier, uint64& objectId) {
		if (!modifier.isEmpty())
			objectId = Long::valueOf(modifier);
		else
			objectId = 0;
	}

	RevivePack* findRevivePack(CreatureObject* creature) {
		Inventory* inventory = creature->getInventory();
		int medicineUse = creature->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->objectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				if (item->isPharmaceutical()) {
					Pharmaceutical* pharma = (Pharmaceutical*) item;

					if (pharma->isRevivePack()) {
						RevivePack* revivePack = (RevivePack*) pharma;

						if (revivePack->getMedicineUseRequired() <= medicineUse)
							return revivePack;
					}
				}
			}
		}

		return NULL;
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		if (!target->isPlayer()) {
			creature->sendSystemMessage("healing_response", "healing_response_a2");	//You cannot apply resuscitation medication without a valid target!
			return 0;
		}

		if (target == creature) {
			creature->sendSystemMessage("You cannot resuscitate yourself.");
			return 0;
		}

		uint64 objectId = 0;

		parseModifier(modifier, objectId);

		RevivePack* revivePack = (RevivePack*) creature->getInventoryItem(objectId);

		if (revivePack == NULL)
			revivePack = findRevivePack(creature);

		Player* playerTarget = (Player*) target;

		if (!canPerformSkill(creature, playerTarget, revivePack))
			return 0;

		int healedHealth = creature->healDamage((CreatureObject*) playerTarget, (int) round(revivePack->getHealthHealed()), CreatureAttribute::HEALTH);
		int healedAction = creature->healDamage((CreatureObject*) playerTarget, (int) round(revivePack->getActionHealed()), CreatureAttribute::ACTION);
		int healedMind = creature->healDamage((CreatureObject*) playerTarget, (int) round(revivePack->getMindHealed()), CreatureAttribute::MIND);

		int healedHealthWounds = creature->healWound((CreatureObject*) playerTarget, (int) round(revivePack->getHealthWoundHealed()), CreatureAttribute::HEALTH);
		int healedActionWounds = creature->healWound((CreatureObject*) playerTarget, (int) round(revivePack->getActionWoundHealed()), CreatureAttribute::ACTION);
		int healedMindWounds = creature->healWound((CreatureObject*) playerTarget, (int) round(revivePack->getMindWoundHealed()), CreatureAttribute::MIND);

		((Player*)creature)->sendBattleFatigueMessage((CreatureObject*) playerTarget);

		if (!creature->resurrect((CreatureObject*) playerTarget))
			return 0;

		StringBuffer msgPlayer, msgTarget;
		msgPlayer << "You resuscitate " << playerTarget->getCharacterName().toString() << ".";
		msgTarget << creature->getCharacterName().toString() << " resuscitates you.";

		creature->sendSystemMessage(msgPlayer.toString());
		playerTarget->sendSystemMessage(msgTarget.toString());

		sendHealMessage((Player*) creature, playerTarget, healedHealth, healedAction, healedMind);
		sendWoundMessage((Player*) creature, playerTarget, healedHealthWounds, healedActionWounds, healedMindWounds);

		creature->changeMindBar(-mindCost);

		if (revivePack != NULL)
			revivePack->useCharge((Player*) creature);

		int xpAmount = healedHealth + healedAction + healedMind + healedHealthWounds + healedActionWounds + healedMindWounds + 250;
		awardXp(creature, "medical", xpAmount);

		doAnimations(creature, (CreatureObject*) playerTarget);

		return 0;
	}

	void awardXp(CreatureObject* creature, String type, int power) {
		Player* player = (Player*) creature;

		int amount = (int)round((float)power * 0.5f);

		if (amount <= 0)
			return;

		player->addXp(type, amount, true);
	}

	void sendHealMessage(Player* player, Player* playerTarget, int health, int action, int mind) {
		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (health > 0 && action > 0 && mind > 0) {
			msgBody << health << " health, " << action << " action, and " << mind << " mind";
		} else {
			if (health > 0 && action > 0) {
				msgBody << health << " health and " << action << " action";
			} else if (health > 0 && mind > 0) {
				msgBody << health << " health and " << mind << " mind";
			} else if (action > 0 && mind > 0) {
					msgBody << action << " action and " << mind << " mind";
			} else {
				if (health > 0) {
					msgBody << health << " health";
				} else if (action > 0) {
					msgBody << action << " action";
				} else if (mind > 0) {
					msgBody << mind << " mind";
				} else {
					return;
				}
			}

		}

		msgTail << " damage.";

		if (player == playerTarget) {
			msgPlayer << "You heal yourself for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgPlayer.toString());
		} else {
			msgPlayer << "You heal " << playerTarget->getFirstNameProper() << " for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgPlayer.toString());
			msgTarget << player->getFirstNameProper() << " heals you for " << msgBody.toString() << msgTail.toString();
			playerTarget->sendSystemMessage(msgTarget.toString());
		}
	}

	void sendWoundMessage(Player* player, Player* playerTarget, int health, int action, int mind) {
		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (health > 0 && action > 0 && mind > 0) {
			msgBody << health << " health, " << action << " action, and " << mind << " mind";
		} else {
			if (health > 0 && action > 0) {
				msgBody << health << " health and " << action << " action";
			} else if (health > 0 && mind > 0) {
				msgBody << health << " health and " << mind << " mind";
			} else if (action > 0 && mind > 0) {
					msgBody << action << " action and " << mind << " mind";
			} else {
				if (health > 0) {
					msgBody << health << " health";
				} else if (action > 0) {
					msgBody << action << " action";
				} else if (mind > 0) {
					msgBody << mind << " mind";
				} else {
					return;
				}
			}

		}

		msgTail << " wound damage.";

		if (player == playerTarget) {
			msgPlayer << "You heal yourself for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgPlayer.toString());
		} else {
			msgPlayer << "You heal " << playerTarget->getFirstNameProper() << " for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgPlayer.toString());
			msgTarget << player->getFirstNameProper() << " heals you for " << msgBody.toString() << msgTail.toString();
			playerTarget->sendSystemMessage(msgTarget.toString());
		}
	}

	float calculateSpeed(CreatureObject* creature) {
		return 0.0f; //Handled by event
	}

	virtual bool calculateCost(CreatureObject* creature) {
		return true;
	}

	void setEffectName(const String& name) {
		effectName = name;
	}

	void setMindCost(int cost) {
		mindCost = cost;
	}

};

#endif /*REVIVETARGETSKILL_H_*/
