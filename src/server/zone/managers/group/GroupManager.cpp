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

#include "../../../chat/room/ChatRoom.h"

#include "../../packets.h"

#include "../../objects/group/GroupObjectImplementation.h"

#include "../../objects/player/Player.h"
#include "../../objects/group/GroupObject.h"

GroupManager::GroupManager() {
}

void GroupManager::inviteToGroup(Player* leader, Player* player) {
	// Pre: leader locked
	// Post: player invited to leader's group, leader locked
	try {
		player->wlock(leader);

		if (leader->isInAGroup()) {
			GroupObject* group = leader->getGroupObject();

			if (group->getLeader() != leader) {
				leader->sendSystemMessage("group", "must_be_leader");
				player->unlock();
				return;
			}
		}

		if (player->isInAGroup()) {
			leader->sendSystemMessage("group", "already_grouped", player->getObjectID());
			player->unlock();
			return;
		}

		if (player->getGroupInviterID() == leader->getObjectID()) {
			leader->sendSystemMessage("group", "considering_your_group", player->getObjectID());
			player->unlock();
			return;
		} else if (player->getGroupInviterID() != 0) {
			stringstream msg;
			msg << player->getCharacterName().c_str() << " is considering joining another group.";
			leader->sendSystemMessage(msg.str());
			player->unlock();
			msg.str("");
			return;
		}

		player->updateGroupInviterId(leader->getObjectID());

		player->sendSystemMessage("group", "invite_target", leader->getObjectID());
		leader->sendSystemMessage("group", "invite_leader", player->getObjectID());

		player->unlock();
	} catch (...) {
		cout << "Exception in GroupManager::inviteToGroup(GroupObject* group, Player* player)\n";
		player->unlock();
	}
}

void GroupManager::joinGroup(Player* player) {
	//Pre: player locked
	//Post: player locked
	uint64 inviterID = player->getGroupInviterID();

	ZoneServer* server = player->getZone()->getZoneServer();
	SceneObject* object = server->getObject(inviterID);

	if (object == NULL || !object->isPlayer() || object == player)
		return;

	Player* inviter = (Player*)object;
	GroupObject* group = NULL;

	try {
		inviter->wlock(player);

		group = inviter->getGroupObject();

		if (group == NULL)
			group = createGroup(inviter);

		inviter->unlock();
	} catch (Exception& e) {
		e.printStackTrace();
		inviter->unlock();

		return;
	} catch (...) {
		cout << "Exception in GroupManager::joinGroup(Player* player)\n";
		inviter->unlock();

		return;
	}

	try {
		group->wlock(player);

		if (group->getGroupSize() == 20) {
			group->unlock();

			player->updateGroupInviterId(0);

			player->sendSystemMessage("group", "full");
			return;
		}

		player->info("joining group");

		group->addPlayer(player);
		player->setGroup(group);
		player->updateGroupId(group->getObjectID());
		player->sendSystemMessage("group", "joined_self");


		ChatRoom* groupChannel = group->getGroupChannel();

		groupChannel->sendTo(player);
		groupChannel->addPlayer(player, false);

		player->updateGroupInviterId(0);

		group->unlock();
	} catch (...) {
		group->unlock();
		cout << "Exception in GroupManager::joinGroup(Player* player)\n";
	}
}

GroupObject* GroupManager::createGroup(Player* leader) {
	// Pre: leader locked
	// Post: GroupObject is a new group with leader, leader locked.

	ZoneServer* server = leader->getZone()->getZoneServer();

	GroupObject* group = new GroupObject(server->getNextCreatureID(), leader, false);

	group->setZone(leader->getZone());

	group->sendTo(leader);

	leader->setGroup(group);
	leader->updateGroupId(group->getObjectID());
	leader->sendSystemMessage("group", "formed_self");

	if (leader->getGroupInviterID() != 0)
		leader->updateGroupInviterId(0);

	return group;
}

void GroupManager::joinGuildGroup(Player* player) {
	//Pre: player locked
	//Post: player locked

	if (player->getGuildID() == 0)
		return;

	Guild* playerGuild = player->getGuild();
	//No Null Check: Player has always a guild (Default guild (unguilded) is 0 )

	playerGuild->wlock();
	ChatRoom* guildchat = playerGuild->getGuildChat();
	playerGuild->unlock();

	if (guildchat == 0) {
		GroupObject* group = NULL;
		group = createGuildGroup(player);
	} else {
		player->unlock();

		guildchat->sendTo(player);
		guildchat->addPlayer(player, false);

		player->wlock();
	}
}

GroupObject* GroupManager::createGuildGroup(Player* play) {
	// Pre: play locked
	// Post: GroupObject is a new group with play, play locked.

	ZoneServer* server = play->getZone()->getZoneServer();

	GroupObject* group = new GroupObject(server->getNextCreatureID(), play, true);
	group->setZone(play->getZone());

	return group;
}

void GroupManager::leaveGroup(GroupObject* group, Player* player) {
	// Pre: player locked
	// Post: player locked
	if (group == NULL)
		return;

	bool destroyGroup = false;

	ChatRoom* groupChannel = group->getGroupChannel();
	groupChannel->removePlayer(player, false);
	groupChannel->sendDestroyTo(player);

	ChatRoom* room = groupChannel->getParent();
	room->sendDestroyTo(player);

	player->setGroup(NULL);
	player->updateGroupId(0);

	if (player != NULL && player->isOnline() && !player->isLoggingOut())
		player->sendSystemMessage("group", "removed");

	player->unlock();

	try {
		group->wlock();

		group->removePlayer(player);

		BaseMessage* msg = new SceneObjectDestroyMessage(group);
		player->sendMessage(msg);

		player->info("leaving group");

		if (group->getGroupSize() < 2) {
			group->disband();
			destroyGroup = true;
		}

		group->unlock();
	} catch (...) {
		group->unlock();
		cout << "Exception in GroupManager::leaveGroup(GroupObject* group, Player* player)\n";
	}

	player->wlock();

	if (destroyGroup)
		group->finalize();
}

void GroupManager::disbandGroup(GroupObject* group, Player* player) {
	//Pre: player locked
	//Post: player locked
	player->unlock();

	try {
		group->wlock();

		if (group->getLeader() != player) {
			player->sendSystemMessage("group", "must_be_leader");
			group->unlock();
			player->wlock();
			return;
		}


		for (int i = 0; i < group->getGroupSize(); i++) {
			Player* play = group->getGroupMember(i);

			if (play != NULL && play->isOnline() && !play->isLoggingOut())
				play->sendSystemMessage("group", "disbanded");
		}

		group->disband();

		group->unlock();
	} catch (...) {
		group->unlock();
		cout << "Exception in GroupManager::disbandGroup(GroupObject* group, Player* player)\n";
	}

	player->wlock();

	group->finalize();
}

void GroupManager::kickFromGroup(GroupObject* group, Player* player, Player* playerToKick) {
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

		Player* leader = group->getLeader();

		if (player != leader) {
			player->sendSystemMessage("group", "must_be_leader");

			group->unlock();

			player->wlock();
			return;
		}

		if (group->getGroupSize() - 1 < 2) {
			for (int i = 0; i < group->getGroupSize(); i++) {
				Player* play = group->getGroupMember(i);

				if (play != NULL && play->isOnline() && !play->isLoggingOut())
					play->sendSystemMessage("group", "disbanded");
			}
			group->disband();
			disbanded = true;
		} else {
			group->removePlayer(playerToKick);
			if (playerToKick != NULL && playerToKick->isOnline() && !playerToKick->isLoggingOut())
				playerToKick->sendSystemMessage("group", "removed");

			playerToKick->info("kicking from group");
		}

		group->unlock();

	} catch (...) {
		cout << "Exception in GroupManager::kickFromGroup(GroupObject* group, Player* player, Player* playerToKick)\n";
		group->unlock();
	}

	if (!disbanded) {
		try {
			playerToKick->wlock();

			ChatRoom* groupChannel = group->getGroupChannel();
			groupChannel->removePlayer(playerToKick, false);
			groupChannel->sendDestroyTo(playerToKick);

			ChatRoom* room = groupChannel->getParent();
			room->sendDestroyTo(playerToKick);

			playerToKick->setGroup(NULL);
			playerToKick->updateGroupId(0);

			ZoneClientSession* client = playerToKick->getClient();
			if (client != NULL)
				group->destroy(client);

			playerToKick->unlock();
		} catch (...) {
			cout << "Exception in GroupManager::kickFromGroup(GroupObject* group, Player* player, Player* playerToKick)\n";
			playerToKick->unlock();

		}
	} else
		group->finalize();

	player->wlock();
}

void GroupManager::makeLeader(GroupObject* group, Player* player, Player* newLeader) {
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

		string firstNameLeader;
		firstNameLeader = "[Offline player]";

		if (newLeader != NULL && newLeader->isOnline() && !newLeader->isLoggingOut())
			firstNameLeader= newLeader->getFirstName();

		stringstream message;
		message << firstNameLeader << " is now the group leader.\n";

		for (int i = 0; i < group->getGroupSize(); i++) {
			Player* play = group->getGroupMember(i);

			if (play != NULL && play->isOnline() && !play->isLoggingOut())
				play->sendSystemMessage(message.str());
		}

		group->unlock();
	} catch (...) {
		group->unlock();
		cout << "Exception in GroupManager::makeLeader(GroupObject* group, Player* player, Player* newLeader)\n";
	}
	player->wlock();
}
