/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DECLINECOMMAND_H_
#define DECLINECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/chat/StringIdChatParameter.h"


class DeclineCommand : public QueueCommand {
public:

	DeclineCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		uint64 inviterID = creature->getGroupInviterID();
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(inviterID);

		if (object == nullptr || !object->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* inviter = cast<CreatureObject*>( object.get());

		creature->updateGroupInviterID(0);

		StringIdChatParameter stringId;
		stringId.setStringId("group", "decline_leader");

		stringId.setTT(creature->getDisplayedName());

		inviter->sendSystemMessage(stringId);
		creature->sendSystemMessage("@group:decline_self");

		return SUCCESS;
	}

};

#endif //DECLINECOMMAND_H_

