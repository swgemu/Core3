/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/GroupLootChangedSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/GroupLootPickLooterSuiCallback.h"


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
		StringIdChatParameter stringId;
		stringId.setStringId("group", "considering_other_group"); // %TT is considering joining another group.
		stringId.setTT(target);
		leader->sendSystemMessage(stringId);

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

	player->updateGroup(group);
	group->addMember(player);

	if (player->isPlayerCreature()) {
		player->sendSystemMessage("@group:joined_self");

		//Inform new member who the Master Looter is.
		if (group->getLootRule() == MASTERLOOTER) {
			StringIdChatParameter masterLooter("group","set_new_master_looter");
			masterLooter.setTT(group->getMasterLooterID());
			player->sendSystemMessage(masterLooter);
		}

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

	Locker locker(group);

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

			if (play->isPlayerCreature()) {
				play->sendSystemMessage("@group:disbanded"); //"The group has been disbanded."

				//Close any open Group SUIs.
				ManagedReference<PlayerObject*> ghost = play->getPlayerObject();
				if (ghost != NULL) {
					ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_RULE);
					ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_CHANGED);
					ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_PICK_LOOTER);
				}
			}
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

		StringIdChatParameter message;
		message.setStringId("group", "new_leader"); // %TU is now the group leader.
		message.setTU(newLeader);

		for (int i = 0; i < group->getGroupSize(); i++) {
			Reference<CreatureObject*> play = ( group->getGroupMember(i)).castTo<CreatureObject*>();

			if (play->isPlayerCreature())
				play->sendSystemMessage(message);
		}

		group->unlock();
	} catch (...) {
		group->unlock();

		player->wlock();

		throw;
	}

	player->wlock();
}

	void GroupManager::changeLootRule(GroupObject* group, int newRule) {
		//Pre: group is locked
		//Post: group is locked
		if (group == NULL)
			return;

		if (group->getLootRule() == newRule) //Don't change to the same rule.
			return;

		//This ensures that the loot rule abbreviations are next to the Leader's name.
		if (newRule != MASTERLOOTER || group->getMasterLooterID() == 0)
			group->setMasterLooterID(group->getLeader()->getObjectID());

		String promptText;

		switch (newRule) {
		case FREEFORALL:
			promptText = "@group:selected_free4all";
			break;
		case MASTERLOOTER:
			promptText = "@group:selected_master";
			notifyMasterLooter(group);
			break;
		case LOTTERY:
			promptText = "@group:selected_lotto";
			break;
		case RANDOM:
			promptText = "@group:selected_random";
			break;
		default:
			return; //Invalid Loot Rule Selected. Stop.
		}

		group->setLootRule(newRule);
		group->updateLootRules(); //Send update packet to all members.

		//Notify group members of the new rule with an SUI box.
		for (int i = 0; i < group->getGroupSize(); ++i) {
			ManagedReference<CreatureObject*> member = (group->getGroupMember(i)).castTo<CreatureObject*>();

			if (member == NULL || !member->isPlayerCreature() || member == group->getLeader())
				continue;

			ManagedReference<PlayerObject*> ghost = member->getPlayerObject();
			if (ghost == NULL)
				continue;

			//Close SUI box if already open.
			ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_CHANGED);

			ManagedReference<SuiMessageBox*> sui = new SuiMessageBox(member, SuiWindowType::GROUP_LOOT_CHANGED);
			sui->setPromptTitle("@group:loot_changed"); //"Loot Type Changed."
			sui->setPromptText(promptText);
			sui->setCancelButton(true, "@group:ok");
			sui->setOkButton(true, "@group:leave_group");
			sui->setCallback(new GroupLootChangedSuiCallback(member->getZoneServer()));

			ghost->addSuiBox(sui);
			member->sendMessage(sui->generateMessage());
		}
}

	void GroupManager::changeMasterLooter(GroupObject* group, CreatureObject* newLooter, bool enableRule) {
		//Pre: group is locked
		//Post: group is locked

		if (group == NULL || newLooter == NULL)
			return;

		//Cancel if existing ML is the new ML, but allow picking the same ML in order to switch to the ML rule.
		if (group->getLootRule() == MASTERLOOTER) {
			if (newLooter->getObjectID() == group->getMasterLooterID())
				return;
		}

		//Set the new Master Looter.
		group->setMasterLooterID(newLooter->getObjectID());

		//If group is not set to Master Looter rule, set it now if applicable.
		if (enableRule && group->getLootRule() != MASTERLOOTER)
			changeLootRule(group, MASTERLOOTER);
		else {
			group->updateLootRules(); //Sends group delta packet to members.
			notifyMasterLooter(group);
		}
	}

	void GroupManager::sendMasterLooterList(GroupObject* group, CreatureObject* leader) {
		//Pre: Leader and group are locked
		//Post: Leader and group are locked

		if (group == NULL || leader == NULL)
			return;

		ManagedReference<PlayerObject*> ghost = leader->getPlayerObject();
		if (ghost == NULL)
			return;

		//Close SUI box if already open.
		ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_PICK_LOOTER);

		//Create Master Looter selection list box.
		ManagedReference<SuiListBox*> sui = new SuiListBox(leader, SuiWindowType::GROUP_LOOT_PICK_LOOTER);
		sui->setPromptTitle("@group:master_looter_sui_title"); //"Select Master Looter"
		sui->setPromptText("@group:choose_master_looter"); //"Choose a Master Looter from the list of available players:"
		sui->setCancelButton(true, "@ui:cancel");
		sui->setOkButton(true, "@ui:ok");
		sui->setCallback(new GroupLootPickLooterSuiCallback(leader->getZoneServer()));

		for (int i = 0; i < group->getGroupSize(); ++i) {
			ManagedReference<CreatureObject*> member = (group->getGroupMember(i)).castTo<CreatureObject*>();
				if (member == NULL || !member->isPlayerCreature())
					continue;

			sui->addMenuItem(member->getFirstName(), member->getObjectID());
		}

		//Send list box to the group leader.
		ghost->addSuiBox(sui);
		leader->sendMessage(sui->generateMessage());
	}

	void GroupManager::notifyMasterLooter(GroupObject* group) {
		//Pre: group is locked
		//Post: group is locked

		if (group == NULL)
			return;

		StringIdChatParameter notificationLeader("group","new_master_looter"); //"%TU is now the master looter."
		notificationLeader.setTU(group->getMasterLooterID());

		//Send system message to leader.
		CreatureObject* groupLeader = cast<CreatureObject*>(group->getLeader().get());
		groupLeader->sendSystemMessage(notificationLeader);

		//Send system message to members.
		if (group->getLeader()->getObjectID() == group->getMasterLooterID())
			group->sendSystemMessage(notificationLeader, false);
		else {
			StringIdChatParameter notificationOther("group","set_new_master_looter"); //"The Group Leader has set %TT as the master looter."
			notificationOther.setTT(group->getMasterLooterID());
			group->sendSystemMessage(notificationOther, false);
		}

	}

