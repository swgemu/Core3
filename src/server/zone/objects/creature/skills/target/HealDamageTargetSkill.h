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

#ifndef HEALDAMAGETARGETSKILL_H_
#define HEALDAMAGETARGETSKILL_H_

#include "../TargetSkill.h"
#include "../../../tangible/pharmaceutical/Pharmaceutical.h"
#include "../../../tangible/pharmaceutical/StimPack.h"
#include "../../../tangible/pharmaceutical/RangedStimPack.h"

#include "../../../../managers/player/PlayerManager.h"
#include "../../../../packets/object/CombatAction.h"

class HealDamageTargetSkill : public TargetSkill {
protected:
	String effectName;
	int mindCost;

public:
	HealDamageTargetSkill(const String& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
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

	void doAnimationsRange(CreatureObject* creature, CreatureObject* creatureTarget,int oid,float range) {

		String crc;

		if (range < 10.0f) {
			crc = "throw_grenade_near_healing";
		}
		else if (10.0f <= range && range < 20.f) {
			crc = "throw_grenade_medium_healing";
		}
		else {
			crc = "throw_grenade_far_healing";
		}

		CombatAction* action = new CombatAction(creature, creatureTarget,  crc.hashCode(), 1, 0L);

		creature->broadcastMessage(action);
	}


	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, StimPack* stimPack) {
		if (!creature->canTreatInjuries()) {
			creature->sendSystemMessage("healing_response", "healing_must_wait"); //You must wait before you can do that.
			return false;
		}

		if (stimPack == NULL) {
			creature->sendSystemMessage("healing_response", "healing_response_60"); //No valid medicine found.
			return false;
		}


		if (creature->isProne()) {
			creature->sendSystemMessage("You cannot do that while prone.");
			return false;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot do that while meditating.");
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

		if (creatureTarget->isOvert() && creatureTarget->getFaction() != creature->getFaction()) {
			creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
			return false;
		}

		if (!creatureTarget->hasHealthDamage() && !creatureTarget->hasActionDamage()) {
			if (creatureTarget == creature) {
				creature->sendSystemMessage("healing_response", "healing_response_61"); //You have no damage to heal.
			} else {
				creature->sendSystemMessage("healing_response", "healing_response_63", creatureTarget->getObjectID()); //%NT has no damage to heal.
			}
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

	StimPack* findStimPack(CreatureObject* creature, float range) {
		Inventory* inventory = creature->getInventory();
		int medicineUse = creature->getSkillMod("healing_ability");
		int combatMedicineUse = creature->getSkillMod("combat_healing_ability");

		bool melee = range <= 5.0f;
		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				if (item->isPharmaceutical()) {
					Pharmaceutical* pharma = (Pharmaceutical*) item;

					if (melee && pharma->isStimPack()) {
						StimPack* stimPack = (StimPack*)pharma;

						if (stimPack->getMedicineUseRequired() <= medicineUse)
							return stimPack;
					}
					if (pharma->isRangedStimPack()) {
						RangedStimPack* stimPack = (RangedStimPack*)pharma;

						if (stimPack->getMedicineUseRequired() <= combatMedicineUse && stimPack->getRange(creature))
							return stimPack;
					}
				}
			}
		}

		return NULL;
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {

		if (!target->isPlayer() && !target->isNonPlayerCreature()) {
			creature->sendSystemMessage("healing_response", "healing_response_62"); //Target must be a player or a creature pet in order to heal damage.
			return 0;
		}

		uint64 objectId = 0;

		parseModifier(modifier, objectId);

		StimPack* stimPack = (StimPack*) creature->getInventoryItem(objectId);

		CreatureObject* creatureTarget = (CreatureObject*) target;

		if (creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted())
			creatureTarget = creature;

		if (!canPerformSkill(creature, creatureTarget, stimPack))
			return 0;

		int stimPower = stimPack->calculatePower(creature);
		int healthHealed = creature->healDamage(creatureTarget, stimPower, CreatureAttribute::HEALTH);
		int actionHealed = creature->healDamage(creatureTarget, stimPower, CreatureAttribute::ACTION);

		if (creature->isPlayer())
			((Player*)creature)->sendBattleFatigueMessage(creatureTarget);

		sendHealMessage(creature, creatureTarget, healthHealed, actionHealed);

		creature->changeMindBar(mindCost);

		if (stimPack != NULL)
			stimPack->useCharge((Player*) creature);

		if (creatureTarget != creature)
			awardXp(creature, "medical", (healthHealed + healthHealed)); //No experience for healing yourself.

		if (stimPack->isArea())
			handleArea(creature,creatureTarget,stimPower,stimPack->getArea());

		if (stimPack->isRangedStimPack()) {
			doAnimationsRange(creature, creatureTarget,stimPack->getObjectID(),creature->calculateDistance(creatureTarget));
		} else
			doAnimations(creature, creatureTarget);

		creature->deactivateInjuryTreatment(stimPack->isRangedStimPack());

		return 0;
	}

	void awardXp(CreatureObject* creature, String type, int power) {
		Player* player = (Player*) creature;

		int amount = (int)round((float)power * 0.25f);

		if (amount <= 0)
			return;

		player->addXp(type, amount, true);
	}

	void sendHealMessage(CreatureObject* creature, CreatureObject* creatureTarget, int healthDamage, int actionDamage) {
		Player* player = (Player*) creature;
		Player* playerTarget = (Player*) creatureTarget;

		StringBuffer msgPlayer, msgTarget, msgBody, msgTail;

		if (healthDamage > 0 && actionDamage > 0) {
			msgBody << healthDamage << " health and " << actionDamage << " action";
		} else if (healthDamage > 0) {
			msgBody << healthDamage << " health";
		} else if (actionDamage > 0) {
			msgBody << actionDamage << " action";
		} else {
			return; //No damage to heal.
		}

		msgTail << " damage.";

		if (creature == creatureTarget) {
			msgPlayer << "You heal yourself for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgPlayer.toString());
		} else {
			msgPlayer << "You heal " << playerTarget->getFirstNameProper() << " for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgPlayer.toString());
			msgTarget << player->getFirstNameProper() << " heals you for " << msgBody.toString() << msgTail.toString();
			playerTarget->sendSystemMessage(msgTarget.toString());
		}
	}

	float getSpeed() {
		return 1.0f; //Handled by event
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

	void handleArea(CreatureObject* creature, CreatureObject* areaCenter, int stimPower, float range) {
		server->getCombatManager()->handelMedicArea(creature, areaCenter,this, stimPower, range);
	/*	for (int i = 0; i < areaCenter->inRangeObjectCount(); i++) {
			SceneObject* object = (SceneObject*) (((SceneObjectImplementation*) areaCenter->getInRangeObject(i))->_this);

			if (!object->isPlayer() && !object->isNonPlayerCreature() && !object->isAttackableObject())
				continue;

			if (object == areaCenter)
				continue;

			if (!areaCenter->isInRange(object,range))
				continue;

			CreatureObject* creatureTarget = (CreatureObject*) object;

			if (creatureTarget != creature)
				creatureTarget->lock();

			if (!canPerformSkillNoMessage(creature, creatureTarget)) {
				if (creatureTarget != creature)
						creatureTarget->unlock();
				continue;
			}

			int healthHealed = creature->healDamage(creatureTarget, stimPower, CreatureAttribute::HEALTH);
			int actionHealed = creature->healDamage(creatureTarget, stimPower, CreatureAttribute::ACTION);

			if (creatureTarget->isPlayer())
				((Player*)creature)->sendBattleFatigueMessage(creatureTarget);

			sendHealMessage(creature, creatureTarget, healthHealed, actionHealed);

			if (creatureTarget != creature)
				awardXp(creature, "medical", (healthHealed + healthHealed)); //No experience for healing yourself.

			if (creatureTarget != creature)
				creatureTarget->unlock();
		}*/
	}

	void doAreaMedicActionTarget(CreatureObject* creature, CreatureObject* creatureTarget, int stimPower) {
		int healthHealed = creature->healDamage(creatureTarget, stimPower, CreatureAttribute::HEALTH);
		int actionHealed = creature->healDamage(creatureTarget, stimPower, CreatureAttribute::ACTION);

		if (creatureTarget->isPlayer())
			((Player*)creature)->sendBattleFatigueMessage(creatureTarget);

		sendHealMessage(creature, creatureTarget, healthHealed, actionHealed);

		if (creatureTarget != creature)
			awardXp(creature, "medical", (healthHealed + healthHealed)); //No experience for healing yourself.

	}

	bool checkAreaMedicTarget(CreatureObject* creature, CreatureObject* creatureTarget) {
		if (!creature->canTreatInjuries()) {
			return false;
		}
		if (creatureTarget->isOvert() && creatureTarget->getFaction() != creature->getFaction()) {
			return false;
		}
		if (!creatureTarget->hasHealthDamage() && !creatureTarget->hasActionDamage()) {
			return false;
		}

		return true;
	}

};

#endif /*HEALDAMAGETARGETSKILL_H_*/
