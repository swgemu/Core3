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

#ifndef CMDOTATTACKTARGETSKILL_H_
#define CMDOTATTACKTARGETSKILL_H_

#include "../AttackTargetSkill.h"
#include "../../../../tangible/pharmaceutical/DotPack.h"

#include "../../../../../managers/player/PlayerManager.h"
#include "../../../../../packets/object/CombatAction.h"
#include "../../../CreatureImplementation.h"

class CMDotAttackTargetSkill : public AttackTargetSkill {
protected:
	String effectName;
	int medType;
public:
	CMDotAttackTargetSkill(const String& name, const String& anim, ZoneProcessServerImplementation* serv) : AttackTargetSkill(name, anim, CMDOT, serv) {
		type = CMDOT;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
	}

	void doAnimationsRange(CreatureObject* creature, CreatureObject* creatureTarget,int oid,float range,bool area) {

		String crc;

		if (range < 10.0f) {
			if (area)
				crc = "throw_grenade_near_area_poison";
			else
				crc = "throw_grenade_near_poison";
		}
		else if (10.0f <= range && range < 20.f) {
			if (area)
				crc = "throw_grenade_medium_area_poison";
			else
				crc = "throw_grenade_medium_poison";
		}
		else {
			if (area)
				crc = "throw_grenade_far_area_poison";
			else
				crc = "throw_grenade_far_poison";
		}

		CombatAction* action = new CombatAction(creature, creatureTarget,  crc.hashCode(), 1, 0L);

		creature->broadcastMessage(action);
	}

	/*
	 * Calculates the costs of the skill.
	 * \param creature The creature, that is checked.
	 * \return Returns if costs are applied.
	 */
	virtual bool calculateCost(CreatureObject* creature) {
		if (!creature->isPlayer())
			return true;

		Player* player = (Player*) creature;

		int wpnMind = 150;

		int mindAttackCost = wpnMind - (wpnMind * creature->getFocus() / 1500);

		if (mindAttackCost < 0)
			mindAttackCost = 0;

		if (!player->changeHAMBars(0,0,-mindAttackCost))
			return false;

		return true;
	}


	void parseModifier(const String& modifier, uint64& objectId) {
		if (!modifier.isEmpty())
			objectId = Long::valueOf(modifier);
		else
			objectId = 0;
	}

	DotPack* findDotPack(CreatureObject* creature, float range) {
		Inventory* inventory = creature->getInventory();
		int combatMedicineUse = creature->getSkillMod("combat_healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				if (item->isPharmaceutical()) {
					Pharmaceutical* pharma = (Pharmaceutical*) item;

					if (medType == pharma->getMedpackType()) {
						DotPack* dotPack = (DotPack*)pharma;

						if (dotPack->getMedicineUseRequired() <= combatMedicineUse && dotPack->getRange(creature) >= range)
							return dotPack;
						}
				}
			}
		}
		return NULL;
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {

		//timer
		if (!creature->hasCooldownExpired(getSkillName())) {
			if (creature->isPlayer())
				((Player*)creature)->sendSystemMessage("healing_response", "healing_must_wait");
			return 0;
		} else {
			float modSkill = (float)creature->getSkillMod("healing_range_speed");
			int delay = (int)round(12.0f - (6.0f * modSkill / 100 ));

			creature->addCooldown(getSkillName(),delay* 1000);
		}

		uint64 objectId = 0;

		parseModifier(modifier, objectId);
		ManagedReference<DotPack> dotPack = (DotPack*) creature->getInventoryItem(objectId);

		CreatureObject* creatureTarget = (CreatureObject*) target;

		int dotPower = dotPack->calculatePower(creature);


		if (dotPack != NULL)
			dotPack->useCharge((Player*) creature);

		if (dotPack->isArea())
			handleArea(creature, creatureTarget, dotPack, dotPack->getArea());

		doAnimationsRange(creature, creatureTarget,dotPack->getObjectID(),creature->calculateDistance(creatureTarget),dotPack->isArea());

		//creature->deactivateInjuryTreatment(dotPack->isRangedStimPack());
		StfParameter* params = new StfParameter();

		if (!creatureTarget->isPlayer()) {
			StringBuffer creatureName;
			creatureName << "@" << creatureTarget->getTemplateTypeName() << ":"
					<< creatureTarget->getTemplateName();
			params->addTT(creatureName.toString());
			params->addTU(creatureName.toString());

		} else {
			params->addTT(((Player*)creatureTarget)->getFirstName());
			params->addTU(((Player*)creatureTarget)->getFirstName());
		}

		int dotDMG = 0;


		if (dotPack->isPoisonDeliveryUnit()) {
			if (creature->isPlayer())
					((Player*)creature)->sendSystemMessage("healing","apply_poison_self",params);
			if (creatureTarget->isPlayer())
					((Player*)creatureTarget)->sendSystemMessage("healing","apply_poison_other",params);

			dotDMG = creatureTarget->addDotState(creature,dotPack->getObjectCRC(),CreatureState::POISONED, dotPower, dotPack->getPool(), dotPack->getDuration(),dotPack->getPotency(),creatureTarget->getSkillMod("resistance_poison"));
		}
		else {
			if (creature->isPlayer())
					((Player*)creature)->sendSystemMessage("healing","apply_disease_self",params);
			if (creatureTarget->isPlayer())
					((Player*)creatureTarget)->sendSystemMessage("healing","apply_disease_other",params);

			dotDMG = creatureTarget->addDotState(creature,dotPack->getObjectCRC(),CreatureState::DISEASED, dotPower, dotPack->getPool(), dotPack->getDuration(),dotPack->getPotency(),creatureTarget->getSkillMod("resistance_disease"));
		}

		if (dotDMG) {
			awardXp(creature, "medical", dotDMG); //No experience for healing yourself.
		} else {

			if (creature->isPlayer())
				((Player*)creature)->sendSystemMessage("dot_message","dot_resisted", params);

		}

		return dotDMG;
	}

	void awardXp(CreatureObject* creature, String type, int power) {
		Player* player = (Player*) creature;

		int amount = (int)round((float)power);

		if (amount <= 0)
			return;

		player->addXp(type, amount, true);
	}

	float getSpeed() {
		return 1.0f; //Handled by event
	}

	void setEffectName(const String& name) {
		effectName = name;
	}

	void handleArea(CreatureObject* creature, CreatureObject* areaCenter,Pharmaceutical* pharma, float range) {
		server->getCombatManager()->handelMedicArea(creature, areaCenter,this, pharma, range);
	}

	void doAreaMedicActionTarget(CreatureObject* creature, CreatureObject* creatureTarget, Pharmaceutical* pharma)	{
		DotPack* dotPack = NULL;
		if (pharma->isPoisonDeliveryUnit() || pharma->isDiseaseDeliveryUnit())
			dotPack = (DotPack*) pharma;

		int dotPower = dotPack->calculatePower(creature);

		//sendDotMessage(creature, creatureTarget, dotPower);

		StfParameter* params = new StfParameter();

		if (!creatureTarget->isPlayer()) {
			StringBuffer creatureName;
			creatureName << "@" << creatureTarget->getTemplateTypeName() << ":"
					<< creatureTarget->getTemplateName();
			params->addTT(creatureName.toString());
			params->addTU(creatureName.toString());

		} else {
			params->addTT(((Player*)creatureTarget)->getFirstName());
			params->addTU(((Player*)creatureTarget)->getFirstName());
		}

		int dotDMG = 0;
		if (dotPack->isPoisonDeliveryUnit()) {
			if (creature->isPlayer())
					((Player*)creature)->sendSystemMessage("healing","apply_poison_self",params);
			if (creatureTarget->isPlayer())
					((Player*)creatureTarget)->sendSystemMessage("healing","apply_poison_other",params);

			dotDMG = creatureTarget->addDotState(creature,dotPack->getObjectCRC(),CreatureState::POISONED, dotPower, dotPack->getPool(), dotPack->getDuration(),dotPack->getPotency(),creatureTarget->getSkillMod("resistance_poison"));
		}
		else {
			if (creature->isPlayer())
					((Player*)creature)->sendSystemMessage("healing","apply_disease_self",params);
			if (creatureTarget->isPlayer())
					((Player*)creatureTarget)->sendSystemMessage("healing","apply_disease_other",params);

			dotDMG = creatureTarget->addDotState(creature,dotPack->getObjectCRC(),CreatureState::DISEASED, dotPower, dotPack->getPool(), dotPack->getDuration(),dotPack->getPotency(),creatureTarget->getSkillMod("resistance_disease"));
		}

		if (dotDMG) {
			awardXp(creature, "medical", dotDMG); //No experience for healing yourself.

			creature->setDefender(creatureTarget);
			creatureTarget->addDefender(creature);
			creature->clearState(CreatureState::PEACE);
			((CreatureImplementation*)creatureTarget->_getImplementation())->doAttack(creature, dotDMG);
			creatureTarget->activateRecovery();

		} else {
			if (creature->isPlayer())
				((Player*)creature)->sendSystemMessage("dot_message","dot_resisted", params);

		}
	}

	bool checkAreaMedicTarget(CreatureObject* creature, CreatureObject* targetCreature) {
		if (targetCreature->isIncapacitated() || targetCreature->isDead() || !targetCreature->isAttackable() || !targetCreature->isAttackableBy(creature))
			return false;
		else if (targetCreature->isPlayingMusic())
			targetCreature->stopPlayingMusic();
		else if (targetCreature->isDancing())
			targetCreature->stopDancing();

		if (targetCreature->isPlayer()) {
			Player* targetPlayer = (Player*) targetCreature;

			if (targetPlayer->isImmune()) {
				return false;
			}

			if (creature->isPlayer()) {
				if (!server->getCombatManager()->canAttack((Player*)creature, targetPlayer)) {
					return false;
				}
			}

			if (!targetPlayer->isOnline()) {
				return false;
			}
		}

		return true;
	}

	void setMedType(int tp) {
		medType = tp;
	}

	int getMedType() {
		return medType;
	}

	int calculateDamage(CreatureObject* creature, SceneObject* target) {
		return 0;
	}
};

#endif /*CMDOTATTACKTARGETSKILL_H_*/
