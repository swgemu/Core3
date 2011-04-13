/*
 * RequestQuestTimersAndCountersCommand.h
 *
 *  Created on: Oct 6, 2010
 *      Author: oru
 */

#ifndef REQUESTQUESTTIMERSANDCOUNTERSCOMMAND_H_
#define REQUESTQUESTTIMERSANDCOUNTERSCOMMAND_H_


#include "server/zone/objects/scene/SceneObject.h"

class RequestQuestTimersAndCountersCommand : public QueueCommand {
public:

	RequestQuestTimersAndCountersCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		return SUCCESS;
	}

};

#endif /* REQUESTQUESTTIMERSANDCOUNTERSCOMMAND_H_ */
