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

#ifndef HEALWOUNDCOMMAND_H_
#define HEALWOUNDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/WoundPack.h"
#include "server/zone/objects/tangible/pharmaceutical/RangedStimPack.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/events/InjuryTreatmentTask.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/managers/collision/CollisionManager.h"

class HealWoundCommand : public QueueCommand {
	int mindCost;
	float range;
public:

	HealWoundCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		mindCost = 50;
		range = 6;
		//defaultTime = 0;
	}

	void deactivateWoundTreatment(CreatureObject* creature) {
		float modSkill = (float)creature->getSkillMod("healing_wound_speed");

		int delay = (int)round((modSkill * -(2.0f / 25.0f)) + 20.0f);

		if (creature->hasBuff(BuffCRC::FOOD_HEAL_RECOVERY)) {
			DelayedBuff* buff = cast<DelayedBuff*>( creature->getBuff(BuffCRC::FOOD_HEAL_RECOVERY));

			if (buff != NULL) {
				float percent = buff->getSkillModifierValue("heal_recovery");

				delay = round(delay * (100.0f - percent) / 100.0f);
			}
		}

		//Force the delay to be at least 3 seconds.
		delay = (delay < 3) ? 3 : delay;

		StringIdChatParameter message("healing_response", "healing_response_59");
		Reference<InjuryTreatmentTask*> task = new InjuryTreatmentTask(creature, message, "woundTreatment");
		creature->addPendingTask("woundTreatment", task, delay * 1000);
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		creatureTarget->playEffect("clienteffect/healing_healwound.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	void awardXp(CreatureObject* creature, const String& type, int power) {
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

		int amount = (int)round((float)power * 0.5f);

		if (amount <= 0)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->awardExperience(player, type, amount, true);
	}

	void sendWoundMessage(CreatureObject* object, CreatureObject* target, uint8 attribute, uint32 woundsHealed) {
		if (!object->isPlayerCreature() || !target->isPlayerCreature())
			return;

		CreatureObject* creature = cast<CreatureObject*>( object);
		CreatureObject* creatureTarget = cast<CreatureObject*>(  target);

		String creatureName = creature->getFirstName();
		String creatureTargetName = creatureTarget->getFirstName();

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

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, WoundPack* woundPack) {
		if (!creature->canTreatWounds()) {
			creature->sendSystemMessage("@healing_response:enhancement_must_wait"); //You must wait before you can heal wounds or apply enhancements again.
			return false;
		}

		if (woundPack == NULL) {
			creature->sendSystemMessage("@healing_response:healing_response_60"); //No valid medicine found.
			return false;
		}

		if (creature->getSkillMod("private_medical_rating") <= 0) {
			creature->sendSystemMessage("@healing_response:must_be_near_droid"); //You must be in a hospital, at a campsite, or near a surgical droid to do that.
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

		if (creature->isRidingCreature()) {
			creature->sendSystemMessage("You cannot do that while Riding a Creature.");
			return false;
		}

		if (creature->isMounted()) {
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

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");
			return false;
		}

		if (creature->getHAM(CreatureAttribute::MIND) < mindCost) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return false;
		}

		if (creature != creatureTarget && !CollisionManager::checkLineOfSight(creature, creatureTarget)) {
			creature->sendSystemMessage("@container_error_message:container18");
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

	uint8 findAttribute(CreatureObject* creature, uint8 startAttribute = 0) {
		for (int i = startAttribute; i < 9; ++i) {
			int wounds = creature->getWounds(i);

			if (wounds != 0)
				return i;
		}

		return CreatureAttribute::UNKNOWN;
	}


	WoundPack* findWoundPack(CreatureObject* creature, uint8 attribute) {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		int medicineUse = creature->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
				SceneObject* object = inventory->getContainerObject(i);

				if (!object->isTangibleObject())
					continue;

				TangibleObject* item = cast<TangibleObject*>( object);

				if (item->isPharmaceuticalObject()) {
					PharmaceuticalObject* pharma = cast<PharmaceuticalObject*>( item);

					if (pharma->isWoundPack()) {
						WoundPack* woundPack = cast<WoundPack*>( pharma);

						if (woundPack->getMedicineUseRequired() <= medicineUse && woundPack->getAttribute() == attribute)
							return woundPack;
					}
				}
			}
		}

		return NULL;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL && !object->isCreatureObject()) {
			return INVALIDTARGET;
		} else if (object == NULL)
			object = creature;

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		Locker clocker(creatureTarget, creature);

		if (creatureTarget->isAiAgent() || creatureTarget->isDead() || creatureTarget->isRidingCreature() || creatureTarget->isMounted() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;

		if (!creature->isInRange(creatureTarget, range))
			return TOOFAR;

		uint8 attribute = CreatureAttribute::UNKNOWN;
		uint64 objectId = 0;

		parseModifier(arguments.toString(), attribute, objectId);

		ManagedReference<WoundPack*> woundPack = NULL;

		if (objectId != 0) {
			SceneObject* inventory = creature->getSlottedObject("inventory");

			if (inventory != NULL) {
				woundPack = dynamic_cast<WoundPack*>(inventory->getContainerObject(objectId));
			}
		} else {
			int searchAttribute = -1;

			while (woundPack == NULL) {
				searchAttribute += 1;
				searchAttribute = findAttribute(creatureTarget, searchAttribute);

				if (searchAttribute == CreatureAttribute::UNKNOWN) {
					//creature->sendSystemMessage("@healing_response:healing_response_61");
					creature->sendSystemMessage("@healing_response:healing_response_60"); //No valid medicine found.
					return GENERALERROR;
				}

				woundPack = findWoundPack(creature, searchAttribute);
			}

			attribute = searchAttribute;
		}

		if (!canPerformSkill(creature, creatureTarget, woundPack))
			return GENERALERROR;

		if (creatureTarget->getWounds(attribute) == 0) {
			if (creatureTarget == creature) {
				creature->sendSystemMessage("@healing_response:healing_response_67");
			} else {
				//TODO: Patch the tre later to include a %NT.
				if (creatureTarget->isPlayerCreature()) {
				StringBuffer message;
				message << (cast<CreatureObject*>(creatureTarget))->getFirstName() << " has no wounds of that type to heal.";
				creature->sendSystemMessage(message.toString());
				}
			}

			return 0;
		}

		uint32 woundPower = woundPack->calculatePower(creature, creatureTarget);

		int woundHealed = creatureTarget->healWound(creature, attribute, woundPower);

		woundHealed = abs(woundHealed);

		if (creature->isPlayerCreature() && creatureTarget->isPlayerCreature()) {
			PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
			playerManager->sendBattleFatigueMessage(creature, creatureTarget);
		}

		sendWoundMessage(creature, creatureTarget, attribute, woundHealed);

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);

		deactivateWoundTreatment(creature);

		woundPack->decreaseUseCount();

		if (creatureTarget != creature)
			awardXp(creature, "medical", woundHealed); //No experience for healing yourself.

		doAnimations(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif //HEALWOUNDCOMMAND_H_
