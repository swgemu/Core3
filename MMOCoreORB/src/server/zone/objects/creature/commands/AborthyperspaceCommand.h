/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ABORTHYPERSPACE_H_
#define ABORTHYPERSPACE_H_

#include "QueueCommand.h"

class AborthyperspaceCommand : public QueueCommand {
public:

	AborthyperspaceCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<ShipObject*> ship = cast<ShipObject*>(creature->getRootParent());

		if (ship == nullptr) {
			creature->error("Attempting hyperspace with no ship object");
			return GENERALERROR;
		}

		StringIdChatParameter param;

		if (!ship->isHyperspacing()) {
			param.setStringId("@space/space_interaction:not_hyperspacing");
			creature->sendSystemMessage(param);

			return GENERALERROR;
		}

		Locker lock(ship, creature);
		ship->setHyperspacing(false);

		param.setStringId("@space/space_interaction:hyperspace_aborted");
		creature->sendSystemMessage(param);

		return SUCCESS;
	}

};

#endif //ABORTHYPERSPACE_H_
