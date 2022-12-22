/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "QueueCommand.h"

#ifndef UNSTICKCOMMAND_H_
#define UNSTICKCOMMAND_H_

class UnstickCommand : public QueueCommand {
public:

	UnstickCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->checkCooldownRecovery("unstick")) {
			creature->sendSystemMessage("You can't /unstick yet, please wait a bit before trying again.");
			return GENERALERROR;
		}

		creature->addCooldown("unstick", 1800 * 1000); // Wait 30 mins before they can try again

		if (creature != nullptr)
			creature->error("used /unstick " + arguments.toString());

		creature->sendSystemMessage("@cmd_err:unstick_request_cancelled"); // Unstick request was cancelled

		/*
string/en/cmd_err.stf	7	unstick_in_progress	Unstick in progress
string/en/cmd_err.stf	8	unstick_request_complete	Unstick complete
string/en/cmd_err.stf	9	unstick_request_cancelled	Unstick request was cancelled
		 */

		return SUCCESS;
	}

};

#endif //UNSTICKCOMMAND_H_

