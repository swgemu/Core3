/*
 * CloseLotteryContainerCommand.h
 *
 *  Created on: Aug 26, 2011
 *      Author: da
 */

#ifndef CLOSELOTTERYCONTAINERCOMMAND_H_
#define CLOSELOTTERYCONTAINERCOMMAND_H_

class CloseLotteryContainerCommand : public QueueCommand {
public:

	CloseLotteryContainerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		return SUCCESS;
	}

};

#endif /* CLOSELOTTERYCONTAINERCOMMAND_H_ */
