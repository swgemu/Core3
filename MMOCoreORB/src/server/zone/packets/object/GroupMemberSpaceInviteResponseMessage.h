/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GROUPMEMBERSPACEINVITERESPONSEMESSAGE
#define GROUPMEMBERSPACEINVITERESPONSEMESSAGE

#include "ObjectControllerMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"

class GroupMemberSpaceInviteResponseMessage: public ObjectControllerMessage {
public:
	GroupMemberSpaceInviteResponseMessage(CreatureObject* memberCreo, CreatureObject* pilot, byte decision) : ObjectControllerMessage(pilot->getObjectID(), 0x1B, 0x439) {
		if (pilot == nullptr || memberCreo == nullptr)
			return;

		// Member Responding to Invite
		insertLong(memberCreo->getObjectID());
		// The group members decision
		insertByte(decision);
		// Pilot
		insertLong(pilot->getObjectID());
	}

};
#endif /*GROUPMEMBERSPACEINVITERESPONSEMESSAGE*/
