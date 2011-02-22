/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "GroupManager.h"

#include "../../ZoneServer.h"
#include "../../Zone.h"

#include "../../../chat/room/ChatRoom.h"

#include "../../objects/creature/CreatureObject.h"
#include "../../objects/player/PlayerCreature.h"

#include "../../objects/group/GroupObject.h"
#include "server/chat/StringIdChatParameter.h"
#include "../../managers/object/ObjectManager.h"


GroupManager::GroupManager() {
}

void GroupManager::inviteToGroup(CreatureObject* leader, CreatureObject* player) {
	// Pre: leader locked
	// Post: player invited to leader's group, leader locked

	Locker clocker(player, leader);

	if (leader->isGrouped()) {
		ManagedReference<GroupObject*> group = leader->getGroup();

		if (group->getLeader() != leader) {
			leader->sendSystemMessage("group", "must_be_leader");
			return;
		}
	}

	if (player->isGrouped()) {
		StringIdChatParameter stringId;
		stringId.setStringId("group", "already_grouped");
		stringId.setTT(player);
		leader->sendSystemMessage(stringId);
		//leader->sendSystemMessage("group", "already_grouped", player->getObjectID());

		return;
	}

	if (player->getGroupInviterID() == leader->getObjectID()) {
		StringIdChatParameter stringId;
		stringId.setStringId("group", "considering_your_group");
		stringId.setTT(player);
		leader->sendSystemMessage(stringId);
		//leader->sendSystemMessage("group", "considering_your_group", player->getObjectID());

		return;
	} else if (player->getGroupInviterID() != 0) {
		StringBuffer msg;
		msg << player->getCreatureName().toString() << " is considering joining another group.";
		leader->sendSystemMessage(msg.toString());

		return;
	}

	player->updateGroupInviterID(leader->getObjectID());

	StringIdChatParameter stringId;
	stringId.setStringId("group", "invite_target");
	stringId.setTT(leader);
	player->sendSystemMessage(stringId);

	stringId.setStringId("group", "invite_leader");
	stringId.setTT(player);
	leader->sendSystemMessage(stringId);
}

void GroupManager::joinGroup(CreatureObject* player) {
	//Pre: player locked
	//Post: player locked
	uint64 inviterID = player->getGroupInviterID();

	ZoneServer* server = player->getZone()->getZoneServer();
	ManagedReference<SceneObject*> object = server->getObject(inviterID);

	if (object == NULL || !object->isPlayerCreature() || object == player)
		return;

	CreatureObject* inviter = (CreatureObject*) object.get();
	GroupObject* group = NULL;

	Locker clocker(inviter, player);

	group = inviter->getGroup();

	if (group == NULL) {
		group = createGroup(inviter);

		if (group == NULL)
			return;
	}

	Locker clocker2(group, player);

	if (group->getGroupSize() == 20) {
		clocker.release();

		player->updateGroupInviterID(0);

		player->sendSystemMessage("group", "full");
		return;
	}

	player->info("joining group");

	group->addMember(player);
	player->updateGroup(group);
	player->sendSystemMessage("group", "joined_self");

	ManagedReference<ChatRoom*> groupChannel = group->getGroupChannel();

	if (groupChannel != NULL && player->isPlayerCreature()) {
		groupChannel->sendTo((PlayerCreature*) player);
		groupChannel->addPlayer((PlayerCreature*) player, false);
	}

	player->updateGroupInviterID(0);
}

GroupObject* GroupManager::createGroup(CreatureObject* leader) {
	// Pre: leader locked
	// Post: GroupObject is a new group with leader, leader locked.
	Zone* zone = leader->getZone();

	if (zone == NULL)
		return NULL;

	ZoneServer* server = leader->getZone()->getZoneServer();

	ManagedReference<GroupObject*> group = (GroupObject*) ObjectManager::instance()->createObject(0x13dcb432, 0, "");
	group->initializeLeader(leader);
	group->startChatRoom();
	group->setZone(leader->getZone());

	group->sendTo(leader, true);

	leader->updateGroup(group);
	leader->sendSystemMessage("group", "formed_self");

	if (leader->getGroupInviterID() != 0)
		leader->updateGroupInviterID(0);

	return group;
}

void GroupManager::leaveGroup(ManagedReference<GroupObject*> group, CreatureObject* player) {
	// Pre: player locked
	// Post: player locked
	if (group == NULL)
		return;

	try {
		Locker clocker(group, player);

		ChatRoom* groupChannel = group->getGroupChannel();
		if (groupChannel != NULL && player->isPlayerCreature()) {
			PlayerCreature* playerCreature = (PlayerCreature*) player;
			groupChannel->removePlayer(playerCreature, false);
			groupChannel->sendDestroyTo(playerCreature);

			ChatRoom* room = groupChannel->getParent();
			room->sendDestroyTo(playerCreature);
		}

		player->updateGroup(NULL);

		//if (player != NULL && player->isOnline() && !player->isLoggingOut())
		player->sendSystemMessage("group", "removed");

		player->unlock();

		group->removeMember(player);

		group->sendDestroyTo(player);

		player->info("leaving group");

		if (group->getGroupSize() < 2) {
			group->disband();
		}

	} catch (Exception& e) {
		System::out << e.getMessage();
		e.printStackTrace();

	} catch (...) {
		System::out << "Exception in GroupManager::leaveGroup(GroupObject* group, CreatureObject* player)\n";

		player->wlock();

		throw;
	}

	player->wlock();
}

void GroupManager::disbandGroup(ManagedReference<GroupObject*> group, CreatureObject* player) {
	//Pre: player locked
	//Post: player locked
	player->unlock();

	try {
		group->wlock();
		//The following should never happen, as a check is made in
		//ObjectControlMessage.cpp and removes the player from the group
		//if he's not the leader. Remove?
		//After Fix 13 feb 2009 - Bankler
		if (group->getLeader() != player) {
			player->sendSystemMessage("group", "must_be_leader");
			group->unlock();
			player->wlock();
			return;
		}

		for (int i = 0; i < group->getGroupSize(); i++) {
			CreatureObject* play = (CreatureObject*) group->getGroupMember(i);

			play->sendSystemMessage("group", "disbanded");
		}

		group->disband();

		group->unlock();
	} catch (...) {
		group->unlock();
		System::out << "Exception in GroupManager::disbandGroup(GroupObject* group, CreatureObject* player)\n";

		player->wlock();

		throw;
	}

	player->wlock();
}

void GroupManager::kickFromGroup(ManagedReference<GroupObject*> group, CreatureObject* player, CreatureObject* playerToKick) {
	// Pre: player is locked, group != NULL
	// Post: playerToKick kicked from group

	player->unlock();

	bool disbanded = false;

	try {
		group->wlock();

		if (!group->hasMember(playerToKick)) {
			group->unlock();
			player->wlock();
			return;
		}

		CreatureObject* leader = (CreatureObject*) group->getLeader();

		if (player != leader) {
			player->sendSystemMessage("group", "must_be_leader");

			group->unlock();

			player->wlock();
			return;
		}

		if (group->getGroupSize() - 1 < 2) {
			for (int i = 0; i < group->getGroupSize(); i++) {
				CreatureObject* play = (CreatureObject*) group->getGroupMember(i);

				play->sendSystemMessage("group", "disbanded");
			}
			group->disband();
			disbanded = true;
		} else {
			group->removeMember(playerToKick);

			playerToKick->sendSystemMessage("group", "removed");

			playerToKick->info("kicking from group");
		}

		group->unlock();

	} catch (...) {
		System::out << "Exception in GroupManager::kickFromGroup(GroupObject* group, CreatureObject* player, CreatureObject* playerToKick)\n";
		group->unlock();

		player->wlock();

		throw;
	}

	if (!disbanded) {
		try {
			playerToKick->wlock();

			if (playerToKick->isPlayerCreature()) {
				PlayerCreature* pl = (PlayerCreature*) playerToKick;
				ManagedReference<ChatRoom*> groupChannel = group->getGroupChannel();
				groupChannel->removePlayer(pl, false);
				groupChannel->sendDestroyTo(pl);

				ManagedReference<ChatRoom*> room = groupChannel->getParent();
				room->sendDestroyTo(pl);
			}

			playerToKick->updateGroup(NULL);

			group->sendDestroyTo(playerToKick);

			playerToKick->unlock();
		} catch (...) {
			System::out << "Exception in GroupManager::kickFromGroup(GroupObject* group, CreatureObject* player, CreatureObject* playerToKick)\n";
			playerToKick->unlock();

			player->wlock();

			throw;
		}
	}

	player->wlock();
}

void GroupManager::makeLeader(GroupObject* group, CreatureObject* player, CreatureObject* newLeader) {
	// Pre: player locked
	// Post: player locked
	player->unlock();

	try {
		group->wlock();

		if (group->getLeader() != player) {
			player->sendSystemMessage("group", "must_be_leader");
			group->unlock();
			player->wlock();
			return;
		}

		if (!group->hasMember(newLeader)) {
			group->unlock();
			player->wlock();
			return;
		}

		group->makeLeader(newLeader);

		String firstNameLeader;
		firstNameLeader = "[Offline player]";

		if (newLeader->isPlayerCreature()) {
			PlayerCreature* playerLeader = (PlayerCreature*) newLeader;
			if (playerLeader->isOnline() && !playerLeader->isLoggingOut())
				firstNameLeader= playerLeader->getFirstName();
		}

		StringBuffer message;
		message << firstNameLeader << " is now the group leader.\n";

		for (int i = 0; i < group->getGroupSize(); i++) {
			CreatureObject* play = (CreatureObject*) group->getGroupMember(i);

			play->sendSystemMessage(message.toString());
		}

		group->unlock();
	} catch (...) {
		group->unlock();

		player->wlock();

		System::out << "Exception in GroupManager::makeLeader(GroupObject* group, CreatureObject* player, CreatureObject* newLeader)\n";

		throw;
	}

	player->wlock();
}
