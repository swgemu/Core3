/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNSTICKCOMMAND_H_
#define UNSTICKCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

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

		/*
string/en/cmd_err.stf	7	unstick_in_progress	Unstick in progress
string/en/cmd_err.stf	8	unstick_request_complete	Unstick complete
string/en/cmd_err.stf	9	unstick_request_cancelled	Unstick request was cancelled
		 */

		return SUCCESS;
	}

};

#endif //UNSTICKCOMMAND_H_

