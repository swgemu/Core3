/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GROUPMEMBERSENDSPACEINVITECALLBACK_H_
#define GROUPMEMBERSENDSPACEINVITECALLBACK_H_

#include "ObjectControllerMessageCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/GroupMemberSendSpaceInviteMessage.h"

class GroupMemberSendSpaceInviteCallback : public MessageCallback {
	ObjectControllerMessageCallback* objectControllerMain;
	uint64 groupMemberID;

public:
	GroupMemberSendSpaceInviteCallback(ObjectControllerMessageCallback* objectControllerCallback) : MessageCallback(objectControllerCallback->getClient(), objectControllerCallback->getServer()),
		objectControllerMain(objectControllerCallback), groupMemberID(0) {
	}

	void parse(Message* message) {
		message->shiftOffset(4);
		groupMemberID = message->parseLong();
	}

	void run() {
		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == nullptr)
			return;

		auto zoneServer = player->getZoneServer();

		if (zoneServer == nullptr)
			return;

		ManagedReference<SceneObject*> memberScno = zoneServer->getObject(groupMemberID);

		if (memberScno == nullptr || !memberScno->isPlayerCreature())
			return;

		if ((player->getParentID() != memberScno->getParentID()) || !memberScno->isInRange(player, 7.f))
			return;

		auto groupMember = memberScno.castTo<CreatureObject*>();

		if (groupMember == nullptr)
			return;

		GroupMemberSendSpaceInviteMessage* inviteMsg = new GroupMemberSendSpaceInviteMessage(player, groupMember);
		groupMember->sendMessage(inviteMsg);
	}
};

#endif /* GROUPMEMBERSENDSPACEINVITECALLBACK_H_ */
