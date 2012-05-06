/*
 * QueueCommand.cpp
 *
 *  Created on: 22/05/2010
 *      Author: victor
 */

#include "QueueCommand.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

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
bool QueueCommand::checkInvalidLocomotions(CreatureObject* creature) {
	for (int i = 0; i < invalidLocomotion.size(); ++i) {
		if (invalidLocomotion.get(i) == creature->getLocomotion())
			return false;
	}

	return true;
}

void QueueCommand::onStateFail(CreatureObject* creature, uint32 actioncntr) {
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

	error("unknown invalid state in onStateFail");
}

void QueueCommand::onLocomotionFail(CreatureObject* creature, uint32 actioncntr) {
	if (!checkInvalidLocomotions(creature))
		creature->clearQueueAction(actioncntr, 0, 1, creature->getLocomotion());
}

/*
 * Unsuccessful command completion alerts the player of the invalid state
 */
void QueueCommand::onFail(uint32 actioncntr, CreatureObject* creature, uint32 errorNumber) {
	StringIdChatParameter prm;
	switch (errorNumber) {
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
	default:
		if (addToQueue)
			creature->clearQueueAction(actioncntr);
		break;
	}
}

void QueueCommand::onComplete(uint32 actioncntr, CreatureObject* player, float commandDuration) {
	if (!player->isPlayerCreature())
		return;

	if (addToQueue)
		player->clearQueueAction(actioncntr, commandDuration);
}

