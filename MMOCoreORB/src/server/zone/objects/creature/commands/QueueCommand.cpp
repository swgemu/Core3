/*
 * QueueCommand.cpp
 *
 *  Created on: 22/05/2010
 *      Author: victor
 */

#include "QueueCommand.h"
#include "server/zone/objects/creature/CreatureObject.h"

QueueCommand::QueueCommand(const String& skillname, ZoneProcessServer* serv) : Skill(skillname), Logger() {
	server = serv;

	nameCRC = skillname.hashCode();

	maxRangeToTarget = 0;

	stateMask = 0;
	targetType = 0;
	disabled = false;
	addToQueue = false;

	defaultTime = 0.f;

	cooldown = 0;

	defaultPriority = NORMAL;

	skillType = QUEUECOMMAND;

	setLogging(true);
	setGlobalLogging(true);
	setLoggingName("QueueCommand " + skillname);
}

/*
 * Sets the invalid postures for this command.
 * Parses the string from LUA's. Format: "4,12,13,"
 */
void QueueCommand::setInvalidPostures(const String& postureStr) {
	StringTokenizer tokenizer(postureStr);
	tokenizer.setDelimeter(",");

	String token = "";
	while (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(token);

		if(!token.isEmpty())
			invalidPostures.add(Integer::valueOf(token));
	}
}


/*
 * Checks each invalid posture with the player's current posture
 */
bool QueueCommand::checkInvalidPostures(CreatureObject* creature) {
	for (int i = 0; i < invalidPostures.size(); ++i) {
		if (invalidPostures.get(i) == creature->getPosture())
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

void QueueCommand::onPostureFail(CreatureObject* creature, uint32 actioncntr) {
	/*
	 * SOE is stupid so player postures do NOT match up with their respective client error message
	 * Because of this, we have to have this switch statement to match them up manually
	 * */
	if (!checkInvalidPostures(creature)) {
		switch(creature->getPosture()) {
		case(CreaturePosture::UPRIGHT):
			creature->clearQueueAction(actioncntr, 0, 1, 0);
		break;
		case(CreaturePosture::CROUCHED):
			creature->clearQueueAction(actioncntr, 0, 1, 4);
		break;
		case(CreaturePosture::PRONE):
			creature->clearQueueAction(actioncntr, 0, 1, 7);
		break;
		case(CreaturePosture::SNEAKING):
			creature->clearQueueAction(actioncntr, 0, 1, 5);
		break;
		case(CreaturePosture::BLOCKING):
			creature->clearQueueAction(actioncntr, 0, 1, 21);
		break;
		case(CreaturePosture::CLIMBING):
			creature->clearQueueAction(actioncntr, 0, 1, 10);
		break;
		case(CreaturePosture::FLYING):
			creature->clearQueueAction(actioncntr, 0, 1, 12);
		break;
		case(CreaturePosture::LYINGDOWN):
			creature->clearQueueAction(actioncntr, 0, 1, 13);
		break;
		case(CreaturePosture::SITTING):
			creature->clearQueueAction(actioncntr, 0, 1, 14);
		break;
		case(CreaturePosture::SKILLANIMATING):
			creature->clearQueueAction(actioncntr, 0, 1, 15);
		break;
		case(CreaturePosture::DRIVINGVEHICLE):
			creature->clearQueueAction(actioncntr, 0, 1, 16);
		break;
		case(CreaturePosture::RIDINGCREATURE):
			creature->clearQueueAction(actioncntr, 0, 1, 17);
		break;
		case(CreaturePosture::KNOCKEDDOWN):
			creature->clearQueueAction(actioncntr, 0, 1, 18);
		break;
		case(CreaturePosture::INCAPACITATED):
			creature->clearQueueAction(actioncntr, 0, 1, 19);
		break;
		case(CreaturePosture::DEAD):
			creature->clearQueueAction(actioncntr, 0, 1, 20);
		break;
		default:
			error("unknown invalid posture in onPostureFail");
			creature->clearQueueAction(actioncntr);
			break;
		}
	}
}

/*
 * Unsuccessful command completion alerts the player of the invalid state
 */
void QueueCommand::onFail(uint32 actioncntr, CreatureObject* creature, uint32 errorNumber) {
	switch (errorNumber) {
	case INVALIDSTATE:
		onStateFail(creature, actioncntr);
		break;
	case INVALIDPOSTURE:
		onPostureFail(creature, actioncntr);
		break;
	case INVALIDTARGET:
		if (addToQueue)
			creature->clearQueueAction(actioncntr, 0, 3, 0);
		break;

	case INVALIDWEAPON:
		creature->sendSystemMessage("cbt_spam", "no_attack_wrong_weapon"); // Can't be done with this weapon

		if (addToQueue)
			creature->clearQueueAction(actioncntr);
		break;

	case TOOFAR:
		if (addToQueue)
			creature->clearQueueAction(actioncntr, 0, 4, 0);
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
		((CreatureObject*)player)->clearQueueAction(actioncntr, commandDuration);
}

