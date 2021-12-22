/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef KNEELCOMMAND_H_
#define KNEELCOMMAND_H_

class KneelCommand : public QueueCommand {
public:

	KneelCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->isAiAgent()) {
			if (creature->isNonPlayerCreatureObject() && creature->isDizzied() && System::random(100) < 85) {
				creature->queueDizzyFallEvent();
			} else if (creature->isInCombat()) {
				creature->setPosture(CreaturePosture::CROUCHED);
				creature->doCombatAnimation(STRING_HASHCODE("change_posture"));
			} else {
				creature->setPosture(CreaturePosture::CROUCHED);
			}
		} else {
			if (creature->isDizzied() && System::random(100) < 85) {
				creature->queueDizzyFallEvent();
			} else {
				creature->setPosture(CreaturePosture::CROUCHED, true, true);
			}
		}

		return SUCCESS;
	}

};

#endif //KNEELCOMMAND_H_
