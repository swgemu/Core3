/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef QUICKHEALCOMMAND_H_
#define QUICKHEALCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "server/zone/objects/tangible/pharmaceutical/RangedStimPack.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/events/InjuryTreatmentTask.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/packets/object/CombatAction.h"
#include "server/zone/objects/player/FactionStatus.h"

class QuickHealCommand : public QueueCommand {
	int mindCost;
	int mindWoundCost;

	int healthHealed;
	int actionHealed;
	int mindHealed;

	float speed;
	float range;
public:

	QuickHealCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

		healthHealed = 0;
		actionHealed = 0;
		mindHealed = 0;

		mindCost = 800;
		mindWoundCost = 10;

		speed = 1;
		range = 6;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* creatureTarget) const {
		creatureTarget->playEffect("clienteffect/healing_healdamage.cef", "");

		if (creature == creatureTarget)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	void sendHealMessage(CreatureObject* creature, CreatureObject* creatureTarget, int healthDamage, int actionDamage) const {
		if (!creature->isPlayerCreature())
			return;

		CreatureObject* player = cast<CreatureObject*>(creature);

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
		} else if (creatureTarget->isPlayerCreature()){
			msgPlayer << "You heal " << creatureTarget->getFirstName() << " for " << msgBody.toString() << msgTail.toString();
			msgTarget << player->getFirstName() << " heals you for " << msgBody.toString() << msgTail.toString();

			player->sendSystemMessage(msgPlayer.toString());
			creatureTarget->sendSystemMessage(msgTarget.toString());
		} else {
			msgPlayer << "You heal " << creatureTarget->getDisplayedName() << " for " << msgBody.toString() << msgTail.toString();
			player->sendSystemMessage(msgPlayer.toString());
		}
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		int result = doCommonMedicalCommandChecks(creature);

		if (result != SUCCESS)
			return result;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object != NULL) {
			if (!object->isCreatureObject()) {
				TangibleObject* tangibleObject = dynamic_cast<TangibleObject*>(object.get());

				if (tangibleObject != NULL && tangibleObject->isAttackableBy(creature)) {
					object = creature;
				} else {
					creature->sendSystemMessage("@healing_response:healing_response_99"); //Target must be a player or a creature pet in order to quick heal.
					return GENERALERROR;
				}
			}
		} else {
			object = creature;
		}

		CreatureObject* creatureTarget = cast<CreatureObject*>( object.get());

		Locker clocker(creatureTarget, creature);
		
		if (!creature->isInRange(creatureTarget, range + creatureTarget->getTemplateRadius() + creature->getTemplateRadius()))
			return TOOFAR;		

		if ((creatureTarget->isAiAgent() && !creatureTarget->isPet()) || creatureTarget->isDroidObject() || creatureTarget->isDead() || creatureTarget->isRidingMount() || creatureTarget->isAttackableBy(creature))
			creatureTarget = creature;

		if (creature->isInCombat()) {
			creature->sendSystemMessage("You cannot do that while in Combat.");
			return GENERALERROR;
		}

		if (creatureTarget->isInCombat()) {
			creature->sendSystemMessage("You cannot do that while your target is in Combat.");
			return GENERALERROR;
		}

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help");  //It would be unwise to help such a patient.
			return GENERALERROR;
		}

		if (creature->getHAM(CreatureAttribute::MIND) < abs(mindCost)) {
			creature->sendSystemMessage("@healing_response:not_enough_mind"); //You do not have enough mind to do that.
			return GENERALERROR;
		}

		if (!creatureTarget->hasDamage(CreatureAttribute::HEALTH) && !creatureTarget->hasDamage(CreatureAttribute::ACTION)) {
			if (creatureTarget == creature)
				creature->sendSystemMessage("@healing_response:healing_response_61"); //You have no damage to heal.
			else if (creatureTarget->isPlayerCreature()) {
				StringIdChatParameter stringId("healing_response", "healing_response_63"); //%NT has no damage to heal.
				stringId.setTT(creatureTarget->getObjectID());
				creature->sendSystemMessage(stringId);
			} else {
				StringBuffer message;
				message << creatureTarget->getDisplayedName() << " has no damage to heal.";
				creature->sendSystemMessage(message.toString());
			}

			return GENERALERROR;
		}

		int healPower = (int) round(150 + System::random(600));

		int healedHealth = creatureTarget->healDamage(creature, CreatureAttribute::HEALTH, healPower);
		int healedAction = creatureTarget->healDamage(creature, CreatureAttribute::ACTION, healPower);

		if (creature->isPlayerCreature()) {
			PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
			playerManager->sendBattleFatigueMessage(creature, creatureTarget);
		}

		sendHealMessage(creature, creatureTarget, healedHealth, healedAction);

		creature->inflictDamage(creature, CreatureAttribute::MIND, mindCost, false);
		creature->addWounds(CreatureAttribute::FOCUS, mindWoundCost, true);
		creature->addWounds(CreatureAttribute::WILLPOWER, mindWoundCost, true);

		doAnimations(creature, creatureTarget);

		checkForTef(creature, creatureTarget);

		return SUCCESS;
	}

};

#endif //QUICKHEALCOMMAND_H_
