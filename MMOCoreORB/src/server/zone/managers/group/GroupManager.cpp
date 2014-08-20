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

#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"

#include "server/chat/room/ChatRoom.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "server/zone/objects/group/GroupObject.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"


GroupManager::GroupManager() {
}

bool GroupManager::playerIsInvitingOwnPet(CreatureObject* inviter, CreatureObject* target) {
	return inviter != NULL
			&& target != NULL
			&& target->isPet()
			&& target->getCreatureLinkID() != 0
			&& target->getCreatureLinkID() == inviter->getObjectID();
}

void GroupManager::inviteToGroup(CreatureObject* leader, CreatureObject* target) {
	// Pre: leader locked
	// Post: player invited to leader's group, leader locked

	Locker clocker(target, leader);

	if (target == leader) {
		leader->sendSystemMessage("@group:invite_no_target_self");
		return;
	}

	if (leader->isGrouped()) {
		ManagedReference<GroupObject*> group = leader->getGroup();

		if (playerIsInvitingOwnPet(leader, target)) {
			if (!target->isInRange(leader, 120)) {
				return;
			}
		}
		else if (group->getLeader() != leader) {
			leader->sendSystemMessage("@group:must_be_leader");
			return;
		}

		// can't invite if the group is full
		if (group->getGroupSize() >= 20) {
			leader->sendSystemMessage("@group:full");
			return;
		}
	}

	if (target->isGrouped()) {
		StringIdChatParameter stringId;
		stringId.setStringId("group", "already_grouped");
		stringId.setTT(target);
		leader->sendSystemMessage(stringId);
		//leader->sendSystemMessage("group", "already_grouped", player->getObjectID());

		return;
	}

	if (target->getGroupInviterID() == leader->getObjectID()) {
		StringIdChatParameter stringId;
		stringId.setStringId("group", "considering_your_group");
		stringId.setTT(target);
		leader->sendSystemMessage(stringId);
		//leader->sendSystemMessage("group", "considering_your_group", player->getObjectID());

		return;
	} else if (target->getGroupInviterID() != 0) {
		StringBuffer msg;
		msg << target->getCreatureName().toString() << " is considering joining another group.";
		leader->sendSystemMessage(msg.toString());

		return;
	}

	target->updateGroupInviterID(leader->getObjectID());

	StringIdChatParameter stringId;
	stringId.setStringId("group", "invite_leader");
	stringId.setTT(target->getDisplayedName());
	leader->sendSystemMessage(stringId);

	if (target->isPlayerCreature()) {
		stringId.setStringId("group", "invite_target");
		stringId.setTT(leader->getDisplayedName());
		target->sendSystemMessage(stringId);

	} else if (target->isPet()) {
		unsigned long long ownerId = target->getCreatureLinkID();
		ManagedReference<CreatureObject*> owner = target->getZoneServer()->getObject(ownerId).castTo<CreatureObject*>();

		if (owner != NULL && owner != leader)
			owner->sendSystemMessage("@pet/pet_menu:pet_invited"); // Your pet has been invited to join your group.

		joinGroup(target);
	}

}

void GroupManager::joinGroup(CreatureObject* player) {
	//Pre: player locked
	//Post: player locked
	uint64 inviterID = player->getGroupInviterID();

	Zone* zone = player->getZone();

	if (zone == NULL)
		return;

	ManagedReference<ZoneServer*> server = zone->getZoneServer();
	ManagedReference<SceneObject*> object = server->getObject(inviterID);

	if (object == NULL || !object->isPlayerCreature() || object == player)
		return;

	CreatureObject* inviter = cast<CreatureObject*>( object.get());
	GroupObject* group = NULL;

	Locker clocker(inviter, player);

	group = inviter->getGroup();

	if (group == NULL) {
		group = createGroup(inviter);

		if (group == NULL)
			return;
	}

	Locker clocker2(group, player);

	if (group->getGroupSize() >= 20) {
		clocker.release();

		player->updateGroupInviterID(0);

		player->sendSystemMessage("The group is full.");
		return;
	}

	// if inviter IS in the group but is not the leader
	if (group->getLeader() != inviter && !playerIsInvitingOwnPet(inviter, player)) {
		player->updateGroupInviterID(0);
		StringIdChatParameter param("group", "prose_leader_changed"); // "%TU has abdicated group leadership to %TT."
		param.setTU( inviter->getDisplayedName() );
		param.setTT( group->getLeader()->getDisplayedName() ) ;
		player->sendSystemMessage(param);

		return;
    }

	player->info("joining group");

	group->addMember(player);
	player->updateGroup(group);

	if (player->isPlayerCreature()) {
		player->sendSystemMessage("@group:joined_self");

		// clear invitee's LFG setting once a group is joined
		Reference<PlayerObject*> ghost = player->getSlottedObject("ghost").castTo<PlayerObject*>();
		if (ghost != NULL)
			ghost->clearCharacterBit(PlayerObject::LFG, true);

		ManagedReference<ChatRoom*> groupChannel = group->getGroupChannel();

		if (groupChannel != NULL) {
			groupChannel->sendTo(cast<CreatureObject*>(player));
			groupChannel->addPlayer(cast<CreatureObject*>(player), false);
		}

		if (player->isPlayingMusic()) {
			ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::ENTERTAINING);
			ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*> (facade.get());
			if (session != NULL && session->isPlayingMusic()) {
				String song = session->getPerformanceName();
				String bandSong = group->getBandSong();
				if (bandSong == "") {
					Locker locker(group);

					group->setBandSong(song);
				} else {
					if (bandSong != song) {
						player->sendSystemMessage("@performance:music_join_band_stop"); // You must play the same song as the band.
						session->stopPlayingMusic();
					} else {
						player->sendSystemMessage("@performance:music_join_band_self"); // You join with the band in the currently playing song.
					}
				}
			}
		}
	}

	player->updateGroupInviterID(0);
}

GroupObject* GroupManager::createGroup(CreatureObject* leader) {
	// Pre: leader locked
	// Post: GroupObject is a new group with leader, leader locked.
	Zone* zone = leader->getZone();

	if (zone == NULL)
		return NULL;

	ManagedReference<ZoneServer*> server = leader->getZone()->getZoneServer();

	ManagedReference<GroupObject*> group = cast<GroupObject*>( ObjectManager::instance()->createObject(0x13dcb432, 0, ""));
	group->initializeLeader(leader);
	group->startChatRoom();
	group->setZone(leader->getZone());

	group->sendTo(leader, true);

	leader->updateGroup(group);
	leader->sendSystemMessage("@group:formed_self");

	// clear inviter's LFG setting once a group is created
	Reference<PlayerObject*> ghost = leader->getSlottedObject("ghost").castTo<PlayerObject*>();
	if (ghost != NULL)
		ghost->clearCharacterBit(PlayerObject::LFG, true);

	if (leader->getGroupInviterID() != 0)
		leader->updateGroupInviterID(0);

	// Set the band song if anyone is playing music
	if (leader->isPlayingMusic()) {
		ManagedReference<Facade*> facade = leader->getActiveSession(SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*> (facade.get());

		if (session != NULL && session->isPlayingMusic()) {
			group->setBandSong(session->getPerformanceName());

			for (int i = 0; i < group->getGroupSize(); ++i) {
				Reference<CreatureObject*> groupMember = (group->getGroupMember(i)).castTo<CreatureObject*>();
				if (groupMember == leader) {
					continue;
				} else {
					ManagedReference<Facade*> otherFacade = groupMember->getActiveSession(SessionFacadeType::ENTERTAINING);
					ManagedReference<EntertainingSession*> otherSession = dynamic_cast<EntertainingSession*> (otherFacade.get());

					if (otherSession != NULL && otherSession->isPlayingMusic()) {
						if (otherSession->getPerformanceName() != group->getBandSong()) {
							groupMember->sendSystemMessage("@performance:music_join_band_stop"); // You must play the same song as the band.
							otherSession->stopPlayingMusic();
						} else {
							groupMember->sendSystemMessage("@performance:music_join_band_self"); // You join with the band in the currently playing song.
						}
					}
				}
			}
		}
	} else {
		for (int i = 0; i < group->getGroupSize(); ++i) {
			Reference<CreatureObject*> groupMember = (group->getGroupMember(i)).castTo<CreatureObject*>();
			if (groupMember->isPlayingMusic()) {
				ManagedReference<Facade*> facade = groupMember->getActiveSession(SessionFacadeType::ENTERTAINING);
				ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*> (facade.get());

				if (session != NULL && session->isPlayingMusic()) {
					String bandSong = group->getBandSong();
					String song = session->getPerformanceName();

					if (bandSong == "") {
						group->setBandSong(song);
					} else if (song != bandSong) {
						groupMember->sendSystemMessage("@performance:music_join_band_stop"); // You must play the same song as the band.
						session->stopPlayingMusic();
					} else {
						groupMember->sendSystemMessage("@performance:music_join_band_self"); // You join with the band in the currently playing song.
					}
				}
			}
		}
	}

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
			CreatureObject* playerCreature = cast<CreatureObject*>( player);
			groupChannel->removePlayer(playerCreature, false);
			groupChannel->sendDestroyTo(playerCreature);

			ChatRoom* room = groupChannel->getParent();
			room->sendDestroyTo(playerCreature);
		}

		if (!group->isOtherMemberPlayingMusic(player))
			group->setBandSong("");

		player->updateGroup(NULL);

		//if (player != NULL && player->isOnline() && !player->isLoggingOut())
		if (player->isPlayerCreature())
			player->sendSystemMessage("@group:removed");

		player->unlock();

		group->removeMember(player);

		if (player->isPlayerCreature())
			group->sendDestroyTo(player);

		player->info("leaving group");

		if (group->getGroupSize() < 2) {
			group->disband();
		}

	} catch (Exception& e) {
		System::out << e.getMessage();
		e.printStackTrace();

	} catch (...) {
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
			player->sendSystemMessage("@group:must_be_leader");
			group->unlock();
			player->wlock();
			return;
		}

		for (int i = 0; i < group->getGroupSize(); i++) {
			Reference<CreatureObject*> play = ( group->getGroupMember(i)).castTo<CreatureObject*>();

			if (play->isPlayerCreature())
				play->sendSystemMessage("@group:disbanded");
		}

		group->disband();

		group->unlock();
	} catch (...) {
		group->unlock();

		player->wlock();

		throw;
	}

	player->wlock();
}

void GroupManager::kickFromGroup(ManagedReference<GroupObject*> group, CreatureObject* player, CreatureObject* memberToKick) {
	// Pre: player is locked, group != NULL
	// Post: memberToKick kicked from group

	player->unlock();

	bool disbanded = false;

	try {
		group->wlock();

		if (!group->hasMember(memberToKick)) {
			group->unlock();
			player->wlock();
			return;
		}

		Reference<CreatureObject*> leader = ( group->getLeader()).castTo<CreatureObject*>();

		if (player != leader) {
			player->sendSystemMessage("@group:must_be_leader");

			group->unlock();

			player->wlock();
			return;
		}

		if (group->getGroupSize() - 1 < 2) {
			for (int i = 0; i < group->getGroupSize(); i++) {
				Reference<CreatureObject*> play = ( group->getGroupMember(i)).castTo<CreatureObject*>();

				play->sendSystemMessage("@group:disbanded");
			}
			group->disband();
			disbanded = true;
		} else {
			group->removeMember(memberToKick);

			if (memberToKick->isPlayerCreature())
				memberToKick->sendSystemMessage("@group:removed");

			memberToKick->info("kicking from group");
		}

		group->unlock();

	} catch (...) {
		group->unlock();

		player->wlock();

		throw;
	}

	if (!disbanded) {
		try {
			memberToKick->wlock();

			if (memberToKick->isPlayerCreature()) {
				CreatureObject* pl = cast<CreatureObject*>( memberToKick);
				ManagedReference<ChatRoom*> groupChannel = group->getGroupChannel();
				groupChannel->removePlayer(pl, false);
				groupChannel->sendDestroyTo(pl);

				ManagedReference<ChatRoom*> room = groupChannel->getParent();
				room->sendDestroyTo(pl);
			}

			memberToKick->updateGroup(NULL);

			if (memberToKick->isPlayerCreature())
				group->sendDestroyTo(memberToKick);

			memberToKick->unlock();
		} catch (...) {
			memberToKick->unlock();

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
			player->sendSystemMessage("@group:must_be_leader");
			group->unlock();
			player->wlock();
			return;
		}

		if (!group->hasMember(newLeader) || !newLeader->isPlayerCreature()) {
			group->unlock();
			player->wlock();
			return;
		}

		group->makeLeader(newLeader);

		String firstNameLeader;
		firstNameLeader = "[Offline player]";

		if (newLeader->isPlayerCreature()) {
			CreatureObject* playerLeader = cast<CreatureObject*>( newLeader);

			if (playerLeader->isOnline())
				firstNameLeader= playerLeader->getFirstName();
		}

		StringBuffer message;
		message << firstNameLeader << " is now the group leader.\n";

		for (int i = 0; i < group->getGroupSize(); i++) {
			Reference<CreatureObject*> play = ( group->getGroupMember(i)).castTo<CreatureObject*>();

			if (play->isPlayerCreature())
				play->sendSystemMessage(message.toString());
		}

		group->unlock();
	} catch (...) {
		group->unlock();

		player->wlock();

		throw;
	}

	player->wlock();
}
