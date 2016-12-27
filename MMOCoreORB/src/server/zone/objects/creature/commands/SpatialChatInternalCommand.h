/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SPATIALCHATINTERNALCOMMAND_H_
#define SPATIALCHATINTERNALCOMMAND_H_

class SpatialChatInternalCommand : public QueueCommand {
public:

	SpatialChatInternalCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ChatManager* chatManager = server->getChatManager();
		if (chatManager == NULL)
			return GENERALERROR;

		chatManager->handleSpatialChatInternalMessage(creature, arguments);

		return SUCCESS;
	}

};

#endif //SPATIALCHATINTERNALCOMMAND_H_

