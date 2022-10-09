/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "GroupManager.h"

#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"

#include "server/chat/room/ChatRoom.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/group/GroupObject.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/chat/ChatManager.h"

#include "server/chat/StringIdChatParameter.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/callbacks/GroupLootChangedSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/GroupLootPickLooterSuiCallback.h"
#include "server/zone/packets/object/OpenLotteryWindow.h"
#include "server/zone/objects/player/sessions/LootLotterySession.h"


GroupManager::GroupManager() {
}

bool GroupManager::playerIsInvitingOwnPet(CreatureObject* inviter, CreatureObject* target) {
	return inviter != nullptr
			&& target != nullptr
			&& target->isPet()
			&& target->getCreatureLinkID() != 0
			&& target->getCreatureLinkID() == inviter->getObjectID();
}

void GroupManager::inviteToGroup(CreatureObject* leader, CreatureObject* target) {
	// Pre: leader locked
	// Post: player invited to leader's group, leader locked

	bool galaxyWide = ConfigManager::instance()->getBool("Core3.PlayerManager.GalaxyWideGrouping", false);

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

		if (galaxyWide) {
			stringId.setTT(target->getDisplayedName());
		} else {
			stringId.setTT(target->getObjectID());
		}

		leader->sendSystemMessage(stringId);
		//leader->sendSystemMessage("group", "already_grouped", player->getObjectID());

		return;
	}

	if (target->getGroupInviterID() == leader->getObjectID()) {
		StringIdChatParameter stringId;
		stringId.setStringId("group", "considering_your_group");

		if (galaxyWide) {
			stringId.setTT(target->getDisplayedName());
		} else {
			stringId.setTT(target->getObjectID());
		}

		leader->sendSystemMessage(stringId);
		//leader->sendSystemMessage("group", "considering_your_group", player->getObjectID());

		return;
	} else if (target->getGroupInviterID() != 0) {
		StringIdChatParameter stringId;
		stringId.setStringId("group", "considering_other_group"); // %TT is considering joining another group.

		if (galaxyWide) {
			stringId.setTT(target->getDisplayedName());
		} else {
			stringId.setTT(target->getObjectID());
		}

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

		if (owner != nullptr && owner != leader)
			owner->sendSystemMessage("@pet/pet_menu:pet_invited"); // Your pet has been invited to join your group.

		joinGroup(target);
	}
}

void GroupManager::joinGroup(CreatureObject* player) {
	//Pre: player locked
	//Post: player locked
	uint64 inviterID = player->getGroupInviterID();

	Zone* zone = player->getZone();

	if (zone == nullptr)
		return;

	ManagedReference<ZoneServer*> server = zone->getZoneServer();
	ManagedReference<SceneObject*> object = server->getObject(inviterID);

	if (object == nullptr || !object->isPlayerCreature() || object == player)
		return;

	CreatureObject* inviter = cast<CreatureObject*>( object.get());
	GroupObject* group = nullptr;

	Locker clocker(inviter, player);

	group = inviter->getGroup();

	if (group == nullptr) {
		group = createGroup(inviter);

		if (group == nullptr)
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

	player->debug("joining group");

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
		if (ghost != nullptr)
			ghost->clearPlayerBit(PlayerBitmasks::LFG, true);

		ManagedReference<ChatRoom*> groupChat = group->getChatRoom();
		if (groupChat != nullptr) {
			groupChat->sendTo(cast<CreatureObject*>(player));
			server->getChatManager()->handleChatEnterRoomById(player, groupChat->getRoomID(), -1, true);
		}

		if (player->isPlayingMusic()) {
			ManagedReference<EntertainingSession*> session = player->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

			if (session != nullptr && session->isPlayingMusic()) {
				session->joinBand();
			}
		}
	}

	player->updateGroupInviterID(0);
}

GroupObject* GroupManager::createGroup(CreatureObject* leader) {
	// Pre: leader locked
	// Post: GroupObject is a new group with leader, leader locked.
	Zone* zone = leader->getZone();

	if (zone == nullptr)
		return nullptr;

	ManagedReference<ZoneServer*> server = leader->getZone()->getZoneServer();

	ManagedReference<GroupObject*> group = cast<GroupObject*>( ObjectManager::instance()->createObject(0x13dcb432, 0, ""));

	Locker locker(group);

	group->initializeLeader(leader);
	group->startChatRoom(leader);

	group->sendTo(leader, true);

	leader->updateGroup(group);
	leader->sendSystemMessage("@group:formed_self");

	// clear inviter's LFG setting once a group is created
	Reference<PlayerObject*> ghost = leader->getSlottedObject("ghost").castTo<PlayerObject*>();
	if (ghost != nullptr)
		ghost->clearPlayerBit(PlayerBitmasks::LFG, true);

	if (leader->getGroupInviterID() != 0)
		leader->updateGroupInviterID(0);

	return group;
}

void GroupManager::leaveGroup(ManagedReference<GroupObject*> group, CreatureObject* player) {
	// Pre: player locked
	// Post: player locked
	if (group == nullptr)
		return;

	try {
		ChatRoom* groupChat = group->getChatRoom();
		if (groupChat != nullptr && player->isPlayerCreature()) {
			CreatureObject* playerCreature = cast<CreatureObject*>(player);

			Locker gclocker(groupChat, playerCreature);
			groupChat->removePlayer(playerCreature);
			groupChat->sendDestroyTo(playerCreature);

			ChatRoom* parentRoom = groupChat->getParent();
			if (parentRoom != nullptr)
				parentRoom->sendDestroyTo(playerCreature);
		}

		Locker clocker(group, player);

		player->updateGroup(nullptr);

		//if (player != nullptr && player->isOnline() && !player->isLoggingOut())
		if (player->isPlayerCreature())
			player->sendSystemMessage("@group:removed");

		player->unlock();

		group->removeMember(player);

		if (player->isPlayerCreature())
			group->sendDestroyTo(player);

		player->debug("leaving group");

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
		Locker locker(group);

		//The following should never happen, as a check is made in
		//ObjectControlMessage.cpp and removes the player from the group
		//if he's not the leader. Remove?
		//After Fix 13 feb 2009 - Bankler
		if (group->getLeader() != player) {
			player->sendSystemMessage("@group:must_be_leader");
			player->wlock();
			return;
		}

		for (int i = 0; i < group->getGroupSize(); i++) {
			Reference<CreatureObject*> play = group->getGroupMember(i);

			if (play->isPlayerCreature()) {
				play->sendSystemMessage("@group:disbanded"); //"The group has been disbanded."

				//Close any open Group SUIs.
				ManagedReference<PlayerObject*> ghost = play->getPlayerObject();
				if (ghost != nullptr) {
					ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_RULE);
					ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_CHANGED);
					ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_PICK_LOOTER);
				}
			}
		}

		group->disband();

	} catch (...) {
		player->wlock();

		throw;
	}

	player->wlock();
}

void GroupManager::kickFromGroup(ManagedReference<GroupObject*> group, CreatureObject* player, CreatureObject* memberToKick) {
	// Pre: player is locked, group != nullptr
	// Post: memberToKick kicked from group

	player->unlock();

	bool disbanded = false;

	try {
		Locker locker(group);

		if (!group->hasMember(memberToKick)) {
			player->wlock();
			return;
		}

		Reference<CreatureObject*> leader = group->getLeader();

		if (player != leader) {
			player->sendSystemMessage("@group:must_be_leader");
			player->wlock();
			return;
		}

		if (group->getGroupSize() - 1 < 2) {
			for (int i = 0; i < group->getGroupSize(); i++) {
				Reference<CreatureObject*> play = group->getGroupMember(i);

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

	} catch (...) {
		player->wlock();

		throw;
	}

	if (!disbanded) {
		try {
			Locker mlocker(memberToKick);

			if (memberToKick->isPlayerCreature()) {
				ManagedReference<ChatRoom*> groupChat = group->getChatRoom();
				if(groupChat != nullptr) {
					Locker clocker(groupChat, memberToKick);
					groupChat->removePlayer(memberToKick);
					groupChat->sendDestroyTo(memberToKick);

					ManagedReference<ChatRoom*> parentRoom = groupChat->getParent();
					if (parentRoom != nullptr)
						parentRoom->sendDestroyTo(memberToKick);
				}
			}

			memberToKick->updateGroup(nullptr);

			if (memberToKick->isPlayerCreature())
				group->sendDestroyTo(memberToKick);

		} catch (...) {
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

		bool galaxyWide = ConfigManager::instance()->getBool("Core3.PlayerManager.GalaxyWideGrouping", false);

		StringIdChatParameter message;
		message.setStringId("group", "new_leader"); // %TU is now the group leader.

		if (galaxyWide) {
			message.setTU(newLeader->getDisplayedName());
		} else {
			message.setTU(newLeader->getObjectID());
		}

		for (int i = 0; i < group->getGroupSize(); i++) {
			Reference<CreatureObject*> play = group->getGroupMember(i);

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
		if (group == nullptr)
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

		//Notify group leader of the new rule with a system message.
		StringIdChatParameter leaderMsg(promptText);
		ManagedReference<CreatureObject*> leader = group->getLeader();
		if (leader != nullptr)
			leader->sendSystemMessage(leaderMsg);

		//Notify group members of the new rule with an SUI box.
		for (int i = 0; i < group->getGroupSize(); ++i) {
			ManagedReference<CreatureObject*> member = group->getGroupMember(i);

			if (member == nullptr || !member->isPlayerCreature() || member == group->getLeader())
				continue;

			ManagedReference<PlayerObject*> ghost = member->getPlayerObject();
			if (ghost == nullptr)
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

		if (group == nullptr || newLooter == nullptr)
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

		if (group == nullptr || leader == nullptr)
			return;

		ManagedReference<PlayerObject*> ghost = leader->getPlayerObject();
		if (ghost == nullptr)
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
			ManagedReference<CreatureObject*> member = group->getGroupMember(i);
				if (member == nullptr || !member->isPlayerCreature())
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

		if (group == nullptr)
			return;

		StringIdChatParameter notificationLeader("group","new_master_looter"); //"%TU is now the master looter."
		notificationLeader.setTU(group->getMasterLooterID());

		//Send system message to leader.
		CreatureObject* groupLeader = group->getLeader();
		groupLeader->sendSystemMessage(notificationLeader);

		//Send system message to members.
		if (groupLeader->getObjectID() == group->getMasterLooterID())
			group->sendSystemMessage(notificationLeader, false);
		else {
			StringIdChatParameter notificationOther("group","set_new_master_looter"); //"The Group Leader has set %TT as the master looter."
			notificationOther.setTT(group->getMasterLooterID());
			group->sendSystemMessage(notificationOther, false);
		}
	}

	void GroupManager::createLottery(GroupObject* group, AiAgent* corpse) {
		//Pre: Corpse is locked.
		//Post: Corpse is locked.

		if (group == nullptr || corpse == nullptr)
			return;

		//Create new Lottery session.
		ManagedReference<LootLotterySession*> session = new LootLotterySession(group->getObjectID(), corpse);
		session->initializeSession();
		corpse->addActiveSession(SessionFacadeType::LOOTLOTTERY, session);

		//Get the corpse's inventory.
		SceneObject* lootContainer = corpse->getSlottedObject("inventory");
		if (lootContainer == nullptr)
			return;

		//Set permissions on all loot items to block theft.
		for (int i = 0; i < lootContainer->getContainerObjectsSize(); ++i) {
			SceneObject* lootItem = lootContainer->getContainerObject(i);
			if (lootItem == nullptr)
				continue;

			ContainerPermissions* itemPerms = lootItem->getContainerPermissionsForUpdate();
			if (itemPerms == nullptr)
				continue;

			itemPerms->setDenyPermission("player", ContainerPermissions::OPEN);
			itemPerms->setDenyPermission("player", ContainerPermissions::MOVECONTAINER);
		}

		Locker clocker(group, corpse);

		//Add group members within range to the Lottery.
		for (int i = 0; i < group->getGroupSize(); ++i) {
			ManagedReference<CreatureObject*> member = group->getGroupMember(i);
			if (member == nullptr || !member->isPlayerCreature())
				continue;

			if (!member->isInRange(corpse, 128.f)) {
				StringIdChatParameter tooFar("group","too_far_away_for_lottery__");
				member->sendSystemMessage(tooFar); //"You are too far away from the creature to participate in the lottery."
				continue;
			}

			session->addEligiblePlayer(member);

			//Send Lottery window.
			OpenLotteryWindow* packet = new OpenLotteryWindow(member, lootContainer);
			member->sendMessage(packet);
		}
	}

	void GroupManager::doRandomLoot(GroupObject* group, AiAgent* corpse) {
		//Pre: Corpse is locked.
		//Post: Corpse is locked.

		if (group == nullptr || corpse == nullptr)
			return;

		Locker glocker(group, corpse);

		//Get the corpse's inventory.
		SceneObject* lootContainer = corpse->getSlottedObject("inventory");
		if (lootContainer == nullptr)
			return;
		int totalItems = lootContainer->getContainerObjectsSize();

		//Determine members eligible to receive loot.
		Vector<CreatureObject*> candidates;
		for (int i = 0; i < group->getGroupSize(); ++i) {
			ManagedReference<CreatureObject*> member = group->getGroupMember(i);
			if (member == nullptr || !member->isPlayerCreature())
				continue;

			if (!member->isInRange(corpse, 128.f))
				continue;

			candidates.add(member);
		}

		glocker.release();

		if (candidates.size() < 1) //Should not happen.
			return;

		//Loop through each item and attempt to transfer it to a random member.
		for (int i = totalItems - 1; i >= 0; --i) {
			//Get the loot item.
			SceneObject* object = lootContainer->getContainerObject(i);
				if (object == nullptr)
					continue;

			//Make sure the item is not left on the corpse for another member.
			auto itemPerms = object->getContainerPermissions();
			if (itemPerms == nullptr || itemPerms->getOwnerID() != 0)
				continue;

			//Pick a winner for the item.
			ManagedReference<CreatureObject*> winner = candidates.get(System::random(candidates.size() - 1));
			if (winner == nullptr)
				continue;

			Locker wclocker(winner, corpse);

			//Transfer the item to the winner.
			transferLoot(group, winner, object, true);
		}

		//Reschedule corpse destruction.
		ManagedReference<CreatureObject*> leader = group->getLeader();
		if (leader != nullptr) {
			Locker lclocker(leader, corpse);
			leader->getZoneServer()->getPlayerManager()->rescheduleCorpseDestruction(leader, corpse);
			return;
		}
	}

	void GroupManager::transferLoot(GroupObject* group, CreatureObject* winner, SceneObject* object, bool stillGrouped) {
		//Pre: winner and corpse are locked.
		//Post: winner and corpse are locked.

		if (winner == nullptr || object == nullptr)
			return;

		//Set the winner as owner of the item.
		ContainerPermissions* itemPerms = object->getContainerPermissionsForUpdate();
		if (itemPerms == nullptr)
			return;

		itemPerms->setOwner(winner->getObjectID());

		//Stop other players being able to take the items if left on the corpse (full inventory).
		itemPerms->setDenyPermission("player", ContainerPermissions::OPEN);
		itemPerms->setDenyPermission("player", ContainerPermissions::MOVECONTAINER);

		//Transfer the item to the winner.
		SceneObject* winnerInventory = winner->getSlottedObject("inventory");
		if (winnerInventory == nullptr)
			return;

		if (winnerInventory->isContainerFullRecursive()) {
			StringIdChatParameter full("group", "you_are_full"); //"Your Inventory is full."
			winner->sendSystemMessage(full);
			StringIdChatParameter problem("group", "problem_transferring"); //"There was a problem transferring items to your inventory.  You may pick them up from the corpse."
			winner->sendSystemMessage(problem);

			if (stillGrouped && group != nullptr) {
				StringIdChatParameter unable("group", "unable_to_transfer"); //"Unable to transfer %TO to %TT.  The item is available on the corpse for %TT to retrieve.
				unable.setTO(object->getObjectID());
				unable.setTT(winner->getObjectID());
				group->sendSystemMessage(unable, winner);
			}

		} else {
			if (winner->getZoneServer()->getObjectController()->transferObject(object, winnerInventory, -1, true)) {
				itemPerms->clearDenyPermission("player", ContainerPermissions::OPEN);
				itemPerms->clearDenyPermission("player", ContainerPermissions::MOVECONTAINER);
			}
		}

	}

