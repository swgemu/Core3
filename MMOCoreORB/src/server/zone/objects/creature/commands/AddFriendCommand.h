/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ADDFRIENDCOMMAND_H_
#define ADDFRIENDCOMMAND_H_

#include "server/zone/objects/player/PlayerObject.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/managers/player/PlayerManager.h"

class AddFriendCommand : public QueueCommand {
public:

	AddFriendCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		String nameLower = arguments.toString().toLowerCase();

		Reference<PlayerObject*> ghost =  creature->getSlottedObject("ghost").castTo<PlayerObject*>();

		if (ghost->isIgnoring(nameLower)) {
			StringIdChatParameter param("cmnty", "friend_fail_is_ignored");
			param.setTT(nameLower);
			creature->sendSystemMessage(param);

			return GENERALERROR;
		}

		if (ghost->hasFriend(nameLower)) {
			StringIdChatParameter param("cmnty", "friend_duplicate");
			param.setTT(nameLower);
			creature->sendSystemMessage(param);

			return GENERALERROR;
		}

		if (ghost->getFriendListSize() >= 1000) {
			creature->sendSystemMessage("You have too many friends!");

			return GENERALERROR;
		}

		PlayerManager* playerManager = server->getPlayerManager();

		bool validName = playerManager->existsName(nameLower);

		if (!validName) {
			StringIdChatParameter param("cmnty", "friend_not_found");
			param.setTT(nameLower);
			creature->sendSystemMessage(param);

			return GENERALERROR;
		}

		ghost->addFriend(nameLower);

		return SUCCESS;
	}

};

#endif //ADDFRIENDCOMMAND_H_
