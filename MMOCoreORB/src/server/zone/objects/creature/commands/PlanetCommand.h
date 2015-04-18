/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLANETCOMMAND_H_
#define PLANETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"

class PlanetCommand : public QueueCommand {
public:

	PlanetCommand(const String& name, ZoneProcessServer* server)
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

#endif //PLANETCOMMAND_H_
