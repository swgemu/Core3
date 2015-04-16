/*
 * QueueCommand.cpp
 *
 *  Created on: 22/05/2010
 *      Author: victor
 */

#include "QueueCommand.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/combat/CombatManager.h"

QueueCommand::QueueCommand(const String& skillname, ZoneProcessServer* serv) : Logger() {
	server = serv;

	name = skillname;
	nameCRC = skillname.hashCode();

	maxRangeToTarget = 0;

	commandGroup = 0;

	stateMask = 0;
	targetType = 0;
	disabled = false;
	addToQueue = false;
	admin = false;

	defaultTime = 0.f;

	cooldown = 0;

	defaultPriority = NORMAL;

	setLogging(true);
	setGlobalLogging(true);
	setLoggingName("QueueCommand " + skillname);
}

/*
 * Sets the invalid locomotion for this command.
 * Parses the string from LUA's. Format: "4,12,13,"
 */
void QueueCommand::setInvalidLocomotions(const String& lStr) {
	StringTokenizer tokenizer(lStr);
	tokenizer.setDelimeter(",");

	String token = "";
	while (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(token);

		if(!token.isEmpty())
			invalidLocomotion.add(Integer::valueOf(token));
	}
}


/*
 * Checks each invalid locomotion with the player's current locomotion
 */
bool QueueCommand::checkInvalidLocomotions(CreatureObject* creature) const {
	for (int i = 0; i < invalidLocomotion.size(); ++i) {
		if (invalidLocomotion.get(i) == creature->getLocomotion())
			return false;
	}

	return true;
}

void QueueCommand::onStateFail(CreatureObject* creature, uint32 actioncntr) const {
	if (!addToQueue)
		return;

	uint64 states = stateMask & creature->getStateBitmask();

	uint64 state = 1;
	int num = 0;

	while (num < 34) {
		if (states & state) {

			creature->clearQueueAction(actioncntr, 0, 5, num);
			return;

		}

		state *= 2;
		++num;
	}

	creature->error("unknown invalid state in onStateFail");
}

void QueueCommand::onLocomotionFail(CreatureObject* creature, uint32 actioncntr) const {
	if (!checkInvalidLocomotions(creature))
		creature->clearQueueAction(actioncntr, 0, 1, creature->getLocomotion());
}

/*
 * Unsuccessful command completion alerts the player of the invalid state
 */
void QueueCommand::onFail(uint32 actioncntr, CreatureObject* creature, uint32 errorNumber) const {
	StringIdChatParameter prm;
	switch (errorNumber) {
	case INVALIDSYNTAX:
		creature->sendSystemMessage(getSyntax());
		if (addToQueue)
			creature->clearQueueAction(actioncntr);
		break;
	case INVALIDSTATE:
		onStateFail(creature, actioncntr);
		break;
	case INVALIDLOCOMOTION:
		onLocomotionFail(creature, actioncntr);
		break;
	case INVALIDTARGET:
		if (addToQueue)
			creature->clearQueueAction(actioncntr, 0, 3, 0);
		break;
	case INVALIDWEAPON: // this only gets returned from combat commands
		switch (creature->getWeapon()->getAttackType()) {
		case WeaponObject::RANGEDATTACK:
			creature->sendSystemMessage("@cbt_spam:no_attack_ranged_single");
			break;
		case WeaponObject::MELEEATTACK:
			creature->sendSystemMessage("@cbt_spam:no_attack_melee_single");
			break;
		default:
			creature->sendSystemMessage("@cbt_spam:no_attack_wrong_weapon"); // Can't be done with this weapon
			break;
		}

		if (addToQueue)
			creature->clearQueueAction(actioncntr);
		break;

	case TOOFAR:
		if (addToQueue)
			creature->clearQueueAction(actioncntr, 0, 4, 0);
		break;

	case NOJEDIARMOR:
		creature->sendSystemMessage("@jedi_spam:not_with_armor"); // You cannot use Force powers or lightsaber abilities while wearing armor.
		if (addToQueue)
			creature->clearQueueAction(actioncntr);

		break;

	case NOPRONE:
		if (addToQueue)
			creature->clearQueueAction(actioncntr, 0, 1, 7);

		break;

	case NOKNEELING:
		if (addToQueue)
			creature->clearQueueAction(actioncntr, 0, 1, 4);

		break;
	case INSUFFICIENTPERMISSION:
		creature->sendSystemMessage("@error_message:insufficient_permissions"); //You do not have sufficient permissions to perform the requested action.

		if (addToQueue)
			creature->clearQueueAction(actioncntr);
		break;
	case TOOCLOSE:
		prm.setStringId("combat_effects", "prone_ranged_too_close");
		creature->sendSystemMessage(prm);

		if (addToQueue)
			creature->clearQueueAction(actioncntr);
		break;
	default:
		if (addToQueue)
			creature->clearQueueAction(actioncntr);
		break;
	}
}

void QueueCommand::onComplete(uint32 actioncntr, CreatureObject* player, float commandDuration) const {
	if (!player->isPlayerCreature())
		return;

	if (addToQueue)
		player->clearQueueAction(actioncntr, commandDuration);
}

int QueueCommand::doCommonMedicalCommandChecks(CreatureObject* creature) const {
	if (!checkStateMask(creature))
		return INVALIDSTATE;

	if (!checkInvalidLocomotions(creature))
		return INVALIDLOCOMOTION;

	if (creature->hasAttackDelay() || !creature->checkPostureChangeDelay()) // no message associated with this
		return GENERALERROR;

	if (creature->isProne() || creature->isMeditating() || creature->isSwimming()) {
		creature->sendSystemMessage("@error_message:wrong_state"); //You cannot complete that action while in your current state.
		return GENERALERROR;
	}

	if (creature->isRidingMount()) {
		creature->sendSystemMessage("@error_message:survey_on_mount"); //You cannot perform that action while mounted on a creature or driving a vehicle.
		return GENERALERROR;
	}

	return SUCCESS;
}

void QueueCommand::checkForTef(CreatureObject* creature, CreatureObject* target) const {
	if (!creature->isPlayerCreature() || creature == target)
		return;

	PlayerObject* ghost = creature->getPlayerObject().get();
	if (ghost == NULL)
		return;

	if (target->isPlayerCreature()) {
		PlayerObject* targetGhost = target->getPlayerObject().get();

		if (!CombatManager::instance()->areInDuel(creature, target)
				&& targetGhost != NULL && targetGhost->getFactionStatus() == FactionStatus::OVERT) {
			ghost->updateLastPvpCombatActionTimestamp();
		}
	} else if (target->isPet()) {
		ManagedReference<CreatureObject*> owner = target->getLinkedCreature().get();

		if (owner != NULL && owner->isPlayerCreature()) {
			PlayerObject* ownerGhost = owner->getPlayerObject().get();

			if (!CombatManager::instance()->areInDuel(creature, owner)
					&& ownerGhost != NULL && ownerGhost->getFactionStatus() == FactionStatus::OVERT) {
				ghost->updateLastPvpCombatActionTimestamp();
			}
		}
	}
}
