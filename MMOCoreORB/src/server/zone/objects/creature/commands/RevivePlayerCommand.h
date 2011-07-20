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

#ifndef REVIVEPLAYERCOMMAND_H_
#define REVIVEPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/RevivePack.h"
#include "server/zone/objects/tangible/pharmaceutical/RangedStimPack.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/events/InjuryTreatmentTask.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/packets/object/CombatAction.h"

class RevivePlayerCommand : public QueueCommand {
	float mindCost;
	float range;
public:

	RevivePlayerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
		mindCost = 200;
		range = 7;
	}

	bool canPerformSkill(CreatureObject* creature, CreatureObject* creatureTarget, RevivePack* revivePack) {
		if (!creatureTarget->isDead()) {
			creature->sendSystemMessage("healing_response", "healing_response_a4"); //Your target does not require resuscitation!
			return 0;
		}

		if (revivePack == NULL) {
			creature->sendSystemMessage("healing_response", "cannot_resuscitate_kit"); //You cannot resuscitate someone without a resuscitation kit!
			return false;
		}

		if (!creatureTarget->isResuscitable()) {
			creature->sendSystemMessage("healing_response", "too_dead_to_resuscitate"); //Your target has been dead too long. There is no hope of resuscitation.
			return false;
		}

		if (creature->isProne()) {
			creature->sendSystemMessage("You cannot do that while Prone.");
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

		/*if (creatureTarget->isPlayer() && creature->isPlayer()) {
			Player * pt = (Player *) creatureTarget;
			Player * p = (Player *) creature;

			if (pt->getFaction() != p->getFaction() && !pt->isOnLeave()) {
				creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
				return false;
			}

			if ((pt->isOvert() && !p->isOvert()) || (pt->isCovert() && p->isOnLeave())) {
				creature->sendSystemMessage("healing_response", "unwise_to_help"); //It would be unwise to help such a patient.
				return false;
			}
		}*/

		ManagedReference<GroupObject*> group = creature->getGroup();

		if (group == NULL || !group->hasMember(creatureTarget)) {
			if (creature->isPlayerCreature()) {
				CreatureObject* player = (CreatureObject*) creature;

				//At this point, we know that the creatureTarget is either a player or a creaturePet.
				//TODO: Activate this switch once creature pet's are introduced.
				//Player* consentOwner = (creatureTarget->isPlayer()) ? (Player*) creatureTarget : (CreaturePet*) creatureTarget->getOwner();
				CreatureObject* consentOwner = (CreatureObject*) creatureTarget;

				PlayerObject* ghost = consentOwner->getPlayerObject();

				if (!ghost->hasInConsentList(player->getFirstName().toLowerCase())) {
					creature->sendSystemMessage("healing_response", "must_be_grouped"); //You must be grouped with or have consent from your resuscitation target!
					return false;
				}
				/*if (!player->hasConsentFrom(consentOwner)) {
					creature->sendSystemMessage("healing_response", "must_be_grouped"); //You must be grouped with or have consent from your resuscitation target!
					return false;
				}*/
			} else {
				return false;
			}

		}

		if (creature->getHAM(CreatureAttribute::MIND) < mindCost) {
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

	void awardXp(CreatureObject* creature, const String& type, int power) {
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = (CreatureObject*) creature;

		int amount = (int)round((float)power * 0.5f);

		if (amount <= 0)
			return;

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		playerManager->awardExperience(player, type, amount, true);
	}

	RevivePack* findRevivePack(CreatureObject* creature) {
		SceneObject* inventory = creature->getSlottedObject("inventory");
		int medicineUse = creature->getSkillMod("healing_ability");

		if (inventory != NULL) {
			for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
				SceneObject* object = inventory->getContainerObject(i);

				if (!object->isTangibleObject())
					continue;

				TangibleObject* item = (TangibleObject*) object;

				if (item->isPharmaceuticalObject()) {
					PharmaceuticalObject* pharma = (PharmaceuticalObject*) item;

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

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) {
		creatureTarget->playEffect("clienteffect/healing_healwound.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL && !object->isCreatureObject()) {
			return INVALIDTARGET;
		} else if (object == NULL)
			object = creature;

		CreatureObject* creatureTarget = (CreatureObject*) object.get();

		Locker clocker(creatureTarget, creature);

		/*if (!target->isPlayer() && !((CreatureObject*)target)->isPet()) {
			creature->sendSystemMessage("healing_response", "healing_response_a2");	//You cannot apply resuscitation medication without a valid target!
			return 0;
		}*/

		if (!creatureTarget->isPlayerCreature()) {
			creature->sendSystemMessage("healing_response", "healing_response_a2");	//You cannot apply resuscitation medication without a valid target!
			return GENERALERROR;
		}

		if (creatureTarget == creature) {
			creature->sendSystemMessage("You cannot resuscitate yourself.");
			return 0;
		}

		if (!creatureTarget->isInRange(creature, range))
			return TOOFAR;

		uint64 objectId = 0;

		parseModifier(arguments.toString(), objectId);

		ManagedReference<RevivePack*> revivePack = NULL;

		SceneObject* inventory = creature->getSlottedObject("inventory");

		if (inventory != NULL) {
			revivePack = dynamic_cast<RevivePack*>(inventory->getContainerObject(objectId));
		}

		if (revivePack == NULL)
			revivePack = findRevivePack(creature);

		if (!canPerformSkill(creature, creatureTarget, revivePack))
			return 0;

		int healthToHeal = MAX(1, (int) round(revivePack->getHealthHealed()));
		int actionToHeal = MAX(1, (int) round(revivePack->getActionHealed()));
		int mindToHeal = MAX(1, (int) round(revivePack->getMindHealed()));

		int healedHealth = creatureTarget->healDamage(creature, CreatureAttribute::HEALTH, healthToHeal);
		int healedAction = creatureTarget->healDamage(creature, CreatureAttribute::ACTION, actionToHeal);
		int healedMind = creatureTarget->healDamage(creature, CreatureAttribute::MIND, mindToHeal);

		creatureTarget->setPosture(CreaturePosture::UPRIGHT);

		int healedHealthWounds = creatureTarget->addWounds(CreatureAttribute::HEALTH, - (int) (round(revivePack->getHealthWoundHealed())));
		int healedActionWounds = creatureTarget->addWounds(CreatureAttribute::ACTION, - (int) (round(revivePack->getActionWoundHealed())));
		int healedMindWounds = creatureTarget->addWounds(CreatureAttribute::MIND, - (int) (round(revivePack->getMindWoundHealed())));

		//creature->resuscitate(creatureTarget);

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);

		if (revivePack != NULL)
			revivePack->decreaseUseCount();

		int xpAmount = healedHealth + healedAction + healedMind + healedHealthWounds + healedActionWounds + healedMindWounds + 250;
		awardXp(creature, "medical", xpAmount);

		doAnimations(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif //REVIVEPLAYERCOMMAND_H_
