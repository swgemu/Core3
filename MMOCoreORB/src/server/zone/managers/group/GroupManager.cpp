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
#include "../../objects/creature/CreatureObject.h"
#include "../../objects/creature/pet/CreaturePet.h"
#include "../../objects/creature/pet/PetCommandHelper.h"

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
			StringBuffer msg;
			msg << player->getCharacterName().toString() << " is considering joining another group.";
			leader->sendSystemMessage(msg.toString());

			player->unlock();
			return;
		}

		player->updateGroupInviterId(leader->getObjectID());

		player->sendSystemMessage("group", "invite_target", leader->getObjectID());
		leader->sendSystemMessage("group", "invite_leader", player->getObjectID());

		player->unlock();
	} catch (...) {
		System::out << "Exception in GroupManager::inviteToGroup(GroupObject* group, Player* player)\n";
		player->unlock();
	}
}

void GroupManager::invitePetToGroup(Player* leader, CreaturePet* pet) {
	// Pre: leader locked
	// Post: player invited to leader's group, leader locked
	try {
		pet->wlock(leader);
		if (!pet->hasCommandTrained(PetCommandHelper::PETGROUP)) {
			leader->sendSystemMessage("not trained");
			pet->unlock();
			return;
		}

		if (leader->isInAGroup()) {
			GroupObject* group = leader->getGroupObject();

			if (group->getLeader() != leader) {
				leader->sendSystemMessage("group", "must_be_leader");
				pet->unlock();
				return;
			}

			if (!group->hasMember(pet->getLinkedCreature())) {
				leader->sendSystemMessage("group", "considering_other_group", pet->getObjectID());
				pet->unlock();
				return;
			}
		}

		if (pet->isInAGroup()) {
			leader->sendSystemMessage("group", "already_grouped", pet->getObjectID());

			pet->unlock();
			return;
		}

		pet->updateGroupInviterId(leader->getObjectID());

		leader->sendSystemMessage("group", "invite_leader", pet->getObjectID());

		pet->unlock();
		try {
		leader->unlock();
		joinGroup(pet);
		leader->lock();
		} catch (...) {
			System::out << "Exception in GroupManager::invitePetToGroup(GroupObject* group, CreatureObject* pet)\n";
			leader->lock();
		}
	} catch (...) {
		System::out << "Exception in GroupManager::invitePetToGroup(GroupObject* group, CreatureObject* pet)\n";
		pet->unlock();
	}
}

void GroupManager::joinGroup(CreatureObject* creatureObject) {
	//Pre: player locked
	//Post: player locked
	uint64 inviterID = creatureObject->getGroupInviterID();

	ZoneServer* server = creatureObject->getZone()->getZoneServer();
	SceneObject* object = server->getObject(inviterID);

	if (object == NULL || (!object->isPlayer() &&
			!(object->isNonPlayerCreature() && ((CreatureObject*)object)->isPet()))
			|| object == creatureObject)
		return;

	Player* inviter = (Player*)object;
	GroupObject* group = NULL;

	try {
		inviter->wlock(creatureObject);

		group = inviter->getGroupObject();

		if (group == NULL)
			group = createGroup(inviter);

		inviter->unlock();
	} catch (Exception& e) {
		e.printStackTrace();
		inviter->unlock();

		return;
	} catch (...) {
		System::out << "Exception in GroupManager::joinGroup(Player* player)\n";
		inviter->unlock();

		return;
	}

	try {
		group->wlock(creatureObject);

		if (group->getGroupSize() == 20) {
			group->unlock();

			creatureObject->updateGroupInviterId(0);
			if (creatureObject->isPlayer())
				((Player*)creatureObject)->sendSystemMessage("group", "full");
			return;
		}

		creatureObject->info("joining group");

		group->addCreature(creatureObject);
		creatureObject->setGroup(group);
		creatureObject->updateGroupId(group->getObjectID());

		if (creatureObject->isPlayer()) {
			Player* player = (Player*)creatureObject;

			player->sendSystemMessage("group", "joined_self");


			ChatRoom* groupChannel = group->getGroupChannel();

			groupChannel->sendTo(player);
			groupChannel->addPlayer(player, false);
		}
		creatureObject->updateGroupInviterId(0);

		group->unlock();
	} catch (...) {
		group->unlock();
		System::out << "Exception in GroupManager::joinGroup(Player* player)\n";
	}
}

GroupObject* GroupManager::createGroup(Player* leader) {
	// Pre: leader locked
	// Post: GroupObject is a new group with leader, leader locked.

	ZoneServer* server = leader->getZone()->getZoneServer();

	GroupObject* group = new GroupObject(server->getNextCreatureID(), leader);

	group->setZone(leader->getZone());

	group->sendTo(leader);

	leader->setGroup(group);
	leader->updateGroupId(group->getObjectID());
	leader->sendSystemMessage("group", "formed_self");

	if (leader->getGroupInviterID() != 0)
		leader->updateGroupInviterId(0);

	return group;
}

void GroupManager::leaveGroup(GroupObject* group, CreatureObject* creatureObject) {
	// Pre: creatureObject locked
	// Post: creatureObject locked
	if (group == NULL)
		return;

	bool destroyGroup = false;

	try {
		group->wlock(creatureObject);

		if (creatureObject->isPlayer()) {
			Player* player = (Player*) creatureObject;
			ChatRoom* groupChannel = group->getGroupChannel();
			if (groupChannel != NULL) {
				groupChannel->removePlayer(player, false);
				groupChannel->sendDestroyTo(player);

				ChatRoom* room = groupChannel->getParent();
				room->sendDestroyTo(player);
			}

		}

		creatureObject->setGroup(NULL);
		creatureObject->updateGroupId(0);

		creatureObject->unlock();

		group->removeCreature(creatureObject);

		if (creatureObject->isPlayer()) {
			Player* player = (Player*) creatureObject;

			if (player != NULL && player->isOnline() && !player->isLoggingOut())
				player->sendSystemMessage("group", "removed");

			BaseMessage* msg = new SceneObjectDestroyMessage(group);
			player->sendMessage(msg);
		}
		creatureObject->info("leaving group");

		if (group->getLeader() == NULL || group->getGroupSize() < 2) {
			group->disband();
			destroyGroup = true;
		}

		group->unlock();
	} catch (...) {
		group->unlock();
		System::out << "Exception in GroupManager::leaveGroup(GroupObject* group, Player* player)\n";
	}

	if (destroyGroup)
		group->finalize();

	creatureObject->wlock();
}

void GroupManager::disbandGroup(GroupObject* group, Player* player) {
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
			CreatureObject* creo = group->getGroupMember(i);

			if (creo->isPlayer()) {
				Player* play = (Player*) creo;
				if (play != NULL && play->isOnline() && !play->isLoggingOut())
					play->sendSystemMessage("group", "disbanded");
			}
		}

		group->disband();

		group->unlock();
	} catch (...) {
		group->unlock();
		System::out << "Exception in GroupManager::disbandGroup(GroupObject* group, Player* player)\n";
	}

	player->wlock();

	group->finalize();
}

void GroupManager::kickFromGroup(GroupObject* group, Player* player, CreatureObject* creatureToKick) {
	// Pre: player is locked, group != NULL
	// Post: playerToKick kicked from group

	player->unlock();

	bool disbanded = false;

	//try {
		group->wlock();

		if (!group->hasMember(creatureToKick)) {
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

		group->removeCreature(creatureToKick);
		if (group->getGroupSize() < 2) {
			for (int i = 0; i < group->getGroupSize(); i++) {

				CreatureObject* creo = group->getGroupMember(i);
				if (creo->isPlayer()) {
					Player* play = (Player*) creo;
					if (play != NULL && play->isOnline() && !play->isLoggingOut())
						play->sendSystemMessage("group", "disbanded");
				}
			}
			group->disband();
			disbanded = true;
		} else {
			if (creatureToKick->isPlayer()) {
				Player* playerToKick =(Player*) creatureToKick;
				if (playerToKick != NULL && playerToKick->isOnline() && !playerToKick->isLoggingOut())
					playerToKick->sendSystemMessage("group", "removed");
			}
			creatureToKick->info("kicking from group");
		}

		group->unlock();

	/*} catch (...) {
		System::out << "Exception in GroupManager::kickFromGroup 1(GroupObject* group, Player* player, Player* playerToKick)\n";
		group->unlock();
	}*/

	if (!disbanded) {
		//try {
			creatureToKick->wlock();
			if (creatureToKick->isPlayer()) {
				Player* playerToKick =(Player*) creatureToKick;
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
			}

			creatureToKick->unlock();
		/*} catch (...) {
			System::out << "Exception in GroupManager::kickFromGroup 2(GroupObject* group, Player* player, Player* playerToKick)\n";
			creatureToKick->unlock();

		}*/
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

		String firstNameLeader;
		firstNameLeader = "[Offline player]";

		if (newLeader != NULL && newLeader->isOnline() && !newLeader->isLoggingOut())
			firstNameLeader= newLeader->getFirstName();

		StringBuffer message;
		message << firstNameLeader << " is now the group leader.\n";

		for (int i = 0; i < group->getGroupSize(); i++) {
			CreatureObject* creo = group->getGroupMember(i);
			if (creo->isPlayer()) {
				Player* play = (Player*) creo;

				if (play != NULL && play->isOnline() && !play->isLoggingOut())
					play->sendSystemMessage(message.toString());
			}
		}

		group->unlock();
	} catch (...) {
		group->unlock();
		System::out << "Exception in GroupManager::makeLeader(GroupObject* group, Player* player, Player* newLeader)\n";
	}
	player->wlock();
}
