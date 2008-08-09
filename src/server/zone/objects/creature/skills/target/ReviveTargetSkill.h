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
	string effectName;
	int mindCost;

public:
	ReviveTargetSkill(const string& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, REVIVE, serv) {
		effectName = aname;
		mindCost = 0;

	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (effectName.size() != 0)
			creatureTarget->playEffect(effectName, "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	RevivePack* findMedpack(CreatureObject* creature, const string& modifier) {
		RevivePack* revivePack = NULL;
		int medicineUse = creature->getSkillMod("healing_ability");

		if (!modifier.empty()) {
			StringTokenizer tokenizer(modifier);
			uint64 objectid = 0;

			if (tokenizer.hasMoreTokens())
				objectid = tokenizer.getLongToken();

			if (objectid > 0) {
				revivePack = (RevivePack*) creature->getInventoryItem(objectid);

				if (revivePack != NULL && revivePack->isRevivePack() && revivePack->getMedicineUseRequired() <= medicineUse) {
					return revivePack;
				}
			}
		}

		Inventory* inventory = creature->getInventory();

		for (int i=0; i<inventory->objectsSize(); i++) {
			TangibleObject* item = (TangibleObject*) inventory->getObject(i);

			if (item != NULL && item->isPharmaceutical()) {
				revivePack = (RevivePack*) item;

				if (revivePack->isRevivePack() && revivePack->getMedicineUseRequired() <= medicineUse)
					return revivePack;
			}
		}

		return NULL; //Never found a revivePack
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const string& modifier, bool doAnimation = true) {
		Player* playerTarget;
		RevivePack* revivePack = NULL;

		int healthWoundHealed = 0;
		int healthHealed = 0;
		int actionWoundHealed = 0;
		int actionHealed = 0;
		int mindWoundHealed = 0;
		int mindHealed = 0;

		int battleFatigue = 0;

		revivePack = findMedpack(creature, modifier);

		if (revivePack == NULL) {
			creature->sendSystemMessage("healing_response", "cannot_resuscitate_kit"); //You cannot resuscitate someone without a resuscitation kit!
			return 0;
		}

		if (target == creature) {
			creature->sendSystemMessage("You cannot resuscitate yourself.");
			return 0;
		}

		if (!target->isPlayer()) {
			creature->sendSystemMessage("healing_response", "healing_response_a2");	//You cannot apply resuscitation medication without a valid target!
			return 0;
		}

		playerTarget = (Player*) target;

		if (!playerTarget->isDead()) {
			creature->sendSystemMessage("healing_response", "healing_response_a4"); //Your target does not require resuscitation!
			return 0;
		}

		/*
		if (!playerTarget->isRevivable()) {
			creature->sendSystemMessage("healing_response", "too_dead_to_resuscitate"); //Your target has been dead too long. There is no hope of resuscitation.
			return 0;
		}*/

		if (creature->isRidingCreature()) {
			creature->sendSystemMessage("You cannot do that while Riding a Creature.");
			return 0;
		}

		if (creature->isMounted()) {
			creature->sendSystemMessage("You cannot do that while Driving a Vehicle.");
			return 0;
		}

		if (playerTarget->isOvert() && playerTarget->getFaction() != creature->getFaction()) {
			creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
			return 0;
		}

		if (!(creature->isInAGroup() && creature->getGroupID() == playerTarget->getGroupID()) && !playerTarget->hasConsent(((Player*)creature)->getFirstName())) {
			creature->sendSystemMessage("healing_response", "must_be_grouped"); //You must be grouped with or have consent from your resuscitation target!
			return 0;
		}

		if (creature->getMind() < abs(mindCost)) {
			creature->sendSystemMessage("healing_response", "not_enough_mind"); //You do not have enough mind to do that.
			return 0;
		}

		battleFatigue = playerTarget->getShockWounds();

		calculateWound(creature, revivePack->getHealthWoundHealed(), battleFatigue, healthWoundHealed);
		calculateHeal(creature, revivePack->getHealthHealed(), battleFatigue, healthHealed);
		calculateWound(creature, revivePack->getActionWoundHealed(), battleFatigue, actionWoundHealed);
		calculateHeal(creature, revivePack->getActionHealed(), battleFatigue, actionHealed);
		calculateWound(creature, revivePack->getMindWoundHealed(), battleFatigue, mindWoundHealed);
		calculateHeal(creature, revivePack->getMindHealed(), battleFatigue, mindHealed);

		sendBFMessage(creature, playerTarget, battleFatigue);

		if (healthWoundHealed > 0)
			playerTarget->changeHealthWoundsBar(-healthWoundHealed);
		if (healthHealed > 0)
			playerTarget->changeHealthBar(healthHealed);

		if (actionWoundHealed > 0)
			playerTarget->changeActionWoundsBar(-actionWoundHealed);
		if (actionHealed > 0)
			playerTarget->changeActionBar(actionHealed);

		if (mindWoundHealed > 0)
			playerTarget->changeMindWoundsBar(-mindWoundHealed);
		if (mindHealed > 0)
			playerTarget->changeMindBar(mindHealed);

		stringstream playerMsg, targetMsg;
		playerMsg << "You resuscitate " << playerTarget->getFirstNameProper() << ".";
		((Player*)creature)->sendSystemMessage(playerMsg.str());
		targetMsg << ((Player*)creature)->getFirstNameProper() << " resuscitates you.";
		playerTarget->sendSystemMessage(targetMsg.str());

		sendHealMessage((Player*)creature, playerTarget, healthHealed, actionHealed, mindHealed);
		sendWoundMessage((Player*)creature, playerTarget, healthWoundHealed, actionWoundHealed, mindWoundHealed);

		playerTarget->revive();

		creature->changeMindBar(-mindCost);

		if (revivePack != NULL)
			revivePack->useCharge((Player*) creature);

		int xpAmount = healthWoundHealed + healthHealed + actionWoundHealed + actionHealed + mindWoundHealed + mindHealed + 250;
		awardXp(creature, "medical", xpAmount);

		doAnimations(creature, (CreatureObject*) playerTarget);

		return 0;
	}

	void calculateHeal(CreatureObject* creature, float basePower, int battleFatigue, int& damageHealed) {
		float modSkill = (float)creature->getSkillMod("healing_injury_treatment");
		int power = (int)round((100.0f + modSkill) / 100.0f * basePower);

		if (battleFatigue >= 1000) {
			power = 1; //Needs to at least be 1 so they are alive!
		} else if (battleFatigue >= 250) {
			power -= (int)round((float)power * (((float)battleFatigue - 250.0f) / 1000.0f));
		}

		damageHealed = power;
	}

	void calculateWound(CreatureObject* creature, float basePower, int battleFatigue, int& damageHealed) {
		float modSkill = (float)creature->getSkillMod("healing_wound_treatment");
		int power = (int)round((100.0f + modSkill) / 100.0f * basePower);

		if (battleFatigue >= 1000) {
			power = 1; //Needs to at least be 1 so they are alive!
		} else if (battleFatigue >= 250) {
			power -= power * ((battleFatigue - 250) / 1000);
		}

		damageHealed = power;
	}

	void awardXp(CreatureObject* creature, string type, int power) {
		Player* player = (Player*) creature;

		int amount = (int)round((float)power * 0.5f);

		if (amount <= 0)
			return;

		player->addXp(type, amount, true);

		String::toLower(type);
		type[0] = toupper(type[0]); //Capitalize first letter.

		stringstream msgExperience;
		msgExperience << "You receive " << amount << " points of " << type << " experience.";
		player->sendSystemMessage(msgExperience.str());
	}

	void sendBFMessage(CreatureObject* creature, CreatureObject* creatureTarget, int battleFatigue) {
		string targetName = ((Player*)creatureTarget)->getFirstNameProper();
		stringstream msgPlayer, msgTarget;

		if (battleFatigue >= 1000) {
			msgPlayer << targetName << "'s battle fatigue is too high for the medicine to do any good.";
			msgTarget << "Your battle fatigue is too high for the medicine to do any good. You should seek an entertainer.";
		} else if (battleFatigue >= 750) {
			msgPlayer << targetName << "'s battle fatgiue is greatly reducing the effectiveness of the medicine.";
			msgTarget << "Your battle fatigue is greatly reducing the effectiveness of the medicine. You should seek an entertainer.";
		} else if (battleFatigue >= 500) {
			msgPlayer << targetName << "'s battle fatigue is significantly reducing the effectiveness of the medicine.";
			msgTarget << "Your battle fatigue is significantly reducing the effectiveness of the medicine.";
		} else if (battleFatigue >= 250) {
			msgPlayer << targetName << "'s battle fatigue is reducing the effectiveness of the medicine.";
			msgTarget << "Your battle fatigue is greatly reducing the effectiveness of the medicine.";
		}

		creatureTarget->sendSystemMessage(msgTarget.str());
		if (creatureTarget != creature) {
			creature->sendSystemMessage(msgPlayer.str());
		}
	}

	void sendHealMessage(Player* player, Player* playerTarget, int health, int action, int mind) {
		stringstream msgPlayer, msgTarget, msgBody, msgTail;

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
			msgPlayer << "You heal yourself for " << msgBody.str() << msgTail.str();
			player->sendSystemMessage(msgPlayer.str());
		} else {
			msgPlayer << "You heal " << playerTarget->getFirstNameProper() << " for " << msgBody.str() << msgTail.str();
			player->sendSystemMessage(msgPlayer.str());
			msgTarget << player->getFirstNameProper() << " heals you for " << msgBody.str() << msgTail.str();
			playerTarget->sendSystemMessage(msgTarget.str());
		}
	}

	void sendWoundMessage(Player* player, Player* playerTarget, int health, int action, int mind) {
		stringstream msgPlayer, msgTarget, msgBody, msgTail;

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
			msgPlayer << "You heal yourself for " << msgBody.str() << msgTail.str();
			player->sendSystemMessage(msgPlayer.str());
		} else {
			msgPlayer << "You heal " << playerTarget->getFirstNameProper() << " for " << msgBody.str() << msgTail.str();
			player->sendSystemMessage(msgPlayer.str());
			msgTarget << player->getFirstNameProper() << " heals you for " << msgBody.str() << msgTail.str();
			playerTarget->sendSystemMessage(msgTarget.str());
		}
	}

	float calculateSpeed(CreatureObject* creature) {
		return 0.0f; //Handled by event
	}

	virtual bool calculateCost(CreatureObject* creature) {
		return true;
	}

	void setEffectName(const string& name) {
		effectName = name;
	}

	void setMindCost(int cost) {
		mindCost = cost;
	}

};

#endif /*REVIVETARGETSKILL_H_*/
