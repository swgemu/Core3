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

#ifndef HEALWOUNDTARGETSKILL_H_
#define HEALWOUNDTARGETSKILL_H_

#include "../TargetSkill.h"
#include "../../../tangible/pharmaceutical/PharmaceuticalImplementation.h"
#include "../../../tangible/pharmaceutical/WoundPackImplementation.h"

#include "../../../../managers/player/PlayerManager.h"

class HealWoundTargetSkill : public TargetSkill {
protected:
	String effectName;
	int mindCost;

public:
	HealWoundTargetSkill(const String& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, HEAL, serv) {
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

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, WoundPack* woundPack) {
		if (!creature->canTreatWounds()) {
			creature->sendSystemMessage("healing_response", "enhancement_must_wait"); //You must wait before you can heal wounds or apply enhancements again.
			return false;
		}

		if (woundPack == NULL) {
			creature->sendSystemMessage("healing_response", "healing_response_60"); //No valid medicine found.
			return false;
		}

		if (creature->getMedicalFacilityRating() <= 0) {
			creature->sendSystemMessage("healing_response", "must_be_near_droid"); //You must be in a hospital, at a campsite, or near a surgical droid to do that.
			return false;
		}

		if (creature->isProne()) {
			creature->sendSystemMessage("You cannot do that while prone.");
			return false;
		}

		if (creature->isMeditating()) {
			creature->sendSystemMessage("You cannot do that while Meditating.");
			return false;
		}

		if (creature->isMountedCreature()) {
			creature->sendSystemMessage("You cannot do that while Riding a Creature.");
			return false;
		}

		if (creature->isRidingMount()) {
			creature->sendSystemMessage("You cannot do that while Driving a Vehicle.");
			return false;
		}

		if (creature->isInCombat()) {
			creature->sendSystemMessage("You cannot do that while in Combat.");
			return false;
		}

		if (creatureTarget->isInCombat()) {
			creature->sendSystemMessage("You cannot do that while your target is in Combat.");
			return false;
		}

		if (creatureTarget->isOvert() && creatureTarget->getFaction() != creature->getFaction()) {
			creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
			return false;
		}

		if (creature->getMind() < abs(mindCost)) {
			creature->sendSystemMessage("healing_response", "not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		return true;
	}

	void parseModifier(const String& modifier, uint8& attribute, uint64& objectId) {
		if (!modifier.isEmpty()) {
			StringTokenizer tokenizer(modifier);
			tokenizer.setDelimeter("|");

			String attributeName;

			tokenizer.getStringToken(attributeName);

			attribute = CreatureAttribute::getAttribute(attributeName);

			if (tokenizer.hasMoreTokens())
				objectId = tokenizer.getLongToken();
		} else {
			attribute = CreatureAttribute::UNKNOWN;
			objectId = 0;
		}
	}

	WoundPack* findWoundPack(CreatureObject* creature, uint8 attribute) {
		Inventory* inventory = creature->getInventory();

		int medicineUse = creature->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				TangibleObject* item = (TangibleObject*) inventory->getObject(i);

				if (item->isPharmaceutical()) {
					Pharmaceutical* pharma = (Pharmaceutical*) item;

					if (pharma->isWoundPack()) {
						WoundPack* woundPack = (WoundPack*) pharma;

						if (woundPack->getMedicineUseRequired() <= medicineUse && woundPack->getAttribute() == attribute)
							return woundPack;
					}
				}
			}
		}

		return NULL;
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		if (!target->isPlayer() && !target->isNonPlayerCreature()) {
			creature->sendSystemMessage("healing_response", "target_must_be_healable"); //Target must be a player or a creature pet in order to tend wounds.
			return 0;
		}

		uint8 attribute = CreatureAttribute::UNKNOWN;
		uint64 objectId = 0;

		parseModifier(modifier, attribute, objectId);

		if (attribute == CreatureAttribute::UNKNOWN) {
			creature->sendSystemMessage("healing_response", "healing_response_75"); //You must specify a valid attribute.
			return 0;
		}

		WoundPack* woundPack = (WoundPack*) creature->getInventoryItem(objectId);

		if (woundPack == NULL)
			woundPack = findWoundPack(creature, attribute);

		CreatureObject* creatureTarget = (CreatureObject*) target;

		if (creatureTarget->isDead() || creatureTarget->isMountedCreature() || creatureTarget->isRidingMount())
			creatureTarget = creature;

		if (!canPerformSkill(creature, creatureTarget, woundPack))
			return 0;

		if (!creatureTarget->hasWound(attribute)) {
			if (creatureTarget == creature) {
				creature->sendSystemMessage("healing_response", "healing_response_67");
			} else {
				//TODO: Patch the tre later to include a %NT.
				StringBuffer message;
				message << creatureTarget->getCharacterName().toString() << " has no wounds of that type to heal.";
				creature->sendSystemMessage(message.toString());
			}
			return 0;
		}

		uint32 woundPower = woundPack->calculatePower(creature, creatureTarget);

		uint32 woundHealed = creature->healWound(creatureTarget, attribute, woundPower);

		if (creature->isPlayer())
			((Player*)creature)->sendBattleFatigueMessage(creatureTarget);

		sendWoundMessage(creature, creatureTarget, attribute, woundHealed);

		creature->changeMindBar(mindCost);

		creature->deactivateWoundTreatment();

		if (woundPack != NULL)
			woundPack->useCharge((Player*) creature);

		if (creatureTarget != creature)
			awardXp(creature, "medical", woundHealed); //No experience for healing yourself.

		doAnimations(creature, creatureTarget);

		return 0;
	}

	void awardXp(CreatureObject* creature, String type, int power) {
		Player* player = (Player*) creature;

		int amount = (int)round((float)power * 0.5f);

		if (amount <= 0)
			return;

		player->addXp(type, amount, true);
	}

	void sendWoundMessage(CreatureObject* creature, CreatureObject* creatureTarget, uint8 attribute, uint32 woundsHealed) {
		String creatureName = creature->getCharacterName().toString();
		String creatureTargetName = creatureTarget->getCharacterName().toString();

		String poolName = CreatureAttribute::getName(attribute);

		StringBuffer msgPlayer, msgTarget, msgTail;

		if (creature == creatureTarget) {
			msgTarget << "You heal yourself for ";
		} else {
			msgPlayer << "You heal " << creatureTargetName << " for ";
			msgTarget << creatureName << " heals you for ";
		}

		msgTail << woundsHealed << " " << poolName << " wound damage.";

		msgTarget << msgTail.toString();
		creatureTarget->sendSystemMessage(msgTarget.toString());

		if (creature != creatureTarget) {
			msgPlayer << msgTail.toString();
			creature->sendSystemMessage(msgPlayer.toString());
		}
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

#endif /*HEALWOUNDTARGETSKILL_H_*/
