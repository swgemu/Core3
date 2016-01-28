/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LAGCOMMAND_H_
#define LAGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class LagCommand : public QueueCommand {
public:

	LagCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer tokenizer(arguments.toString());
		String option;

		if (tokenizer.hasMoreTokens()) {
			tokenizer.getStringToken(option);

			if (option == "setCloseObjectsRange") {
				float range = 192;

				if (tokenizer.hasMoreTokens()) {
					range = tokenizer.getIntToken();
				}

				server->getZoneServer()->changeCloseObjectRange(range);
				creature->sendSystemMessage("Server close objects range changed to " + String::valueOf(range));
			} else if (option == "check") {
				SceneObject* sceno = server->getZoneServer()->getObject(target);

				if (sceno != NULL) {
					if (creature->getCloseObjects()->contains(sceno)) {
						creature->sendSystemMessage("Target is a close object.");
					} else {
						creature->sendSystemMessage("Target is not a close object.");
					}
				} else {
					creature->sendSystemMessage("Target is NULL");
				}
			}

		} else {
			creature->sendSystemMessage("SYNTAX: /lag setCloseObjectsRange [range]");
		}

		return SUCCESS;
	}

};

#endif //LAGCOMMAND_H_
