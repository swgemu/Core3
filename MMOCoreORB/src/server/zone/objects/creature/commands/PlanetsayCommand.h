/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLANETSAYCOMMAND_H_
#define PLANETSAYCOMMAND_H_

#include "server/chat/ChatManager.h"

class PlanetsayCommand : public QueueCommand {
public:

	PlanetsayCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ChatManager* chatManager = server->getZoneServer()->getChatManager();
		chatManager->handlePlanetChat( creature, arguments);

		return SUCCESS;
	}

};

#endif //PLANETSAYCOMMAND_H_
