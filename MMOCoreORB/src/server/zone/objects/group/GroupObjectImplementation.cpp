/*
 * GroupObjectImplementation.cpp
 *
 *  Created on: 29/12/2009
 *      Author: victor
 */

#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/packets/group/GroupObjectMessage3.h"
#include "server/zone/packets/group/GroupObjectMessage6.h"
#include "server/zone/packets/group/GroupObjectDeltaMessage6.h"
#include "server/zone/ZoneClientSession.h"
#include "server/chat/room/ChatRoom.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/objects/creature/buffs/SquadLeaderBuff.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/group/RemovePetsFromGroupTask.h"
#include "server/zone/objects/group/tasks/UpdateNearestMissionForGroupTask.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/managers/creature/PetManager.h"

//#define DEBUG_GROUPS

void GroupObjectImplementation::sendBaselinesTo(SceneObject* player) {
	if (player == nullptr)
		return;

#ifdef DEBUG_GROUPS
	info(true) << "GroupObjectImplementation::sendBaselinesTo -- Player: " << player->getDisplayedName();
#endif

	GroupObjectMessage3* grup3 = new GroupObjectMessage3(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(grup3);

	GroupObjectMessage6* grup6 = new GroupObjectMessage6(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(grup6);
}

void GroupObjectImplementation::startChatRoom(CreatureObject* leader) {
	ChatManager* chatManager = server->getZoneServer()->getChatManager();

	if (chatManager == nullptr) {
		return;
	}

	chatRoom = chatManager->createGroupRoom(getObjectID(), leader);
}

void GroupObjectImplementation::destroyChatRoom() {
	if (chatRoom == nullptr)
		return;

	ChatManager* chatManager = server->getZoneServer()->getChatManager();
	ManagedReference<ChatRoom*> parent = chatRoom->getParent();

	chatManager->destroyRoom(chatRoom);

	if (parent != nullptr)
		chatManager->destroyRoom(parent);

	chatRoom = nullptr;
}

void GroupObjectImplementation::broadcastMessage(BaseMessage* msg) {
	if (msg == nullptr)
		return;

	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* member = getGroupMember(i);

		if (member == nullptr || !member->isPlayerCreature())
			continue;

		member->sendMessage(msg->clone());
	}

	delete msg;
}

void GroupObjectImplementation::broadcastMessage(CreatureObject* player, BaseMessage* msg, bool sendSelf) {
	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* member = getGroupMember(i);

		if (member == nullptr)
			continue;

		if (!sendSelf && player != nullptr && member->getObjectID() == player->getObjectID())
			continue;

		if (member->isPlayerCreature())
			member->sendMessage(msg->clone());
	}

	delete msg;
}

void GroupObjectImplementation::updatePvPStatusNearCreature(CreatureObject* creature) {
	if (creature == nullptr)
		return;

	CloseObjectsVector* creatureCloseObjects = (CloseObjectsVector*) creature->getCloseObjects();
	SortedVector<QuadTreeEntry*> closeObjectsVector;

	if (creatureCloseObjects == nullptr)
		return;

	creatureCloseObjects->safeCopyReceiversTo(closeObjectsVector, CloseObjectsVector::CREOTYPE);

	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* member = getGroupMember(i);

		if (member == nullptr || !closeObjectsVector.contains(member))
			continue;

		if (creature->isPlayerCreature())
			member->sendPvpStatusTo(creature);

		if (member->isPlayerCreature())
			creature->sendPvpStatusTo(member);
	}
}

void GroupObjectImplementation::addMember(CreatureObject* newMember, bool notifyClient) {
	// Pre: Group is locked, newMember is locked

	if (newMember == nullptr)
		return;

#ifdef DEBUG_GROUPS
	info(true) << "Group ID: " << getObjectID() << " Adding Member: " << newMember->getDisplayedName();
#endif

	// Handle player that is piloting ship
	uint64 shipID = 0;

	// Add the meber to the list
	groupMembers.add(newMember);

	if (newMember->isPlayerCreature()) {
		if (notifyClient)
			sendTo(newMember, true);

		if (hasSquadLeader()) {
			addGroupModifiers(newMember);
		}

		scheduleUpdateNearestMissionForGroup(newMember->getPlanetCRC());
	}

	calculateGroupLevel();

	// Send update after group level is recalculated
	if (notifyClient) {
		GroupObjectDeltaMessage6* groupDelta6 = new GroupObjectDeltaMessage6(_this.getReferenceUnsafeStaticCast());

		if (groupDelta6 != nullptr) {
			groupDelta6->updateMembers();
			groupDelta6->close();

			broadcastMessage(groupDelta6);
		}
	}
}

void GroupObjectImplementation::removeMember(CreatureObject* memberRemoved) {
	// Pre: group is locked, member is locked

	if (memberRemoved == nullptr)
		return;

#ifdef DEBUG_GROUPS
	info(true) << "Group ID: " << getObjectID() << " Removing Member: " << memberRemoved->getDisplayedName();
#endif

	uint64 memberRemovedID = memberRemoved->getObjectID();
	bool wasLeader = getLeaderID() == memberRemovedID;

	if (hasSquadLeader()) {
		if (wasLeader)
			removeGroupModifiers();
		else
			removeGroupModifiers(memberRemoved);
	}

	// remove member from the list
	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* member = groupMembers.get(i).get().get();

		if (member ==  nullptr || member->getObjectID() != memberRemovedID)
			continue;

		GroupObjectDeltaMessage6* groupDelta6 = new GroupObjectDeltaMessage6(_this.getReferenceUnsafeStaticCast());

		if (groupDelta6 != nullptr) {
			groupDelta6->startUpdate(0x1);
			groupMembers.remove(i, groupDelta6);
			groupDelta6->close();

			broadcastMessage(groupDelta6);
		}
	}

	if (memberRemoved->isPlayerCreature()) {
		// Remove member's pets
		RemovePetsFromGroupTask* task = new RemovePetsFromGroupTask(memberRemoved, _this.getReferenceUnsafeStaticCast());
		task->execute();

		//Close any open Group SUIs.
		ManagedReference<PlayerObject*> ghost = memberRemoved->getPlayerObject();

		if (ghost != nullptr) {
			ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_RULE);
			ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_CHANGED);
			ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_PICK_LOOTER);

			ghost->removeWaypointBySpecialType(WaypointObject::SPECIALTYPE_NEARESTMISSIONFORGROUP);
		}

		// Reset Master Looter if needed.
		if (getMasterLooterID() == memberRemoved->getObjectID()) {
			ManagedReference<CreatureObject*> groupLeader = getLeader();

			if (groupLeader != nullptr)
				setMasterLooterID(groupLeader->getObjectID());
		}

		if (wasLeader && hasSquadLeader()) {
			addGroupModifiers();
		}

		Zone* zone = memberRemoved->getZone();

		if (zone != nullptr) {
			scheduleUpdateNearestMissionForGroup(zone->getPlanetCRC());
		}
	}

	updatePvPStatusNearCreature(memberRemoved);
	calculateGroupLevel();
}

bool GroupObjectImplementation::hasMember(CreatureObject* player) {
	if (player == nullptr)
		return false;

	uint64 playerID = player->getObjectID();

	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* member = groupMembers.get(i).get().get();

		if (member == nullptr)
			continue;

		if (member->getObjectID() == playerID)
			return true;
	}

	return false;
}

bool GroupObjectImplementation::hasMember(uint64 playerID) {
	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* member = groupMembers.get(i).get().get();

		if (member == nullptr)
			continue;

		if (member->getObjectID() == playerID)
			return true;
	}

	return false;
}

void GroupObjectImplementation::makeLeader(CreatureObject* newLeader) {
	if (groupMembers.size() < 2 || newLeader == nullptr)
		return;

	Reference<CreatureObject*> oldLeader = groupMembers.get(0).get();

	if (oldLeader == nullptr)
		return;

#ifdef DEBUG_GROUPS
	info(true) << "makeLeader -- Current Leader: " << oldLeader->getDisplayedName() << " New Leader: " << newLeader->getDisplayedName();
#endif

	uint64 newLeaderID = newLeader->getObjectID();
	int groupPosition = -1;

	for (int i = 0; i < groupMembers.size(); ++i) {
		CreatureObject* member = groupMembers.get(i).get();

		if (member == nullptr || member->getObjectID() != newLeaderID)
			continue;

		groupPosition = i;
		break;
	}

	if (groupPosition < 0)
		return;

	if (hasSquadLeader())
		removeGroupModifiers();

	GroupObjectDeltaMessage6* groupDelta6 = new GroupObjectDeltaMessage6(_this.getReferenceUnsafeStaticCast());

	if (groupDelta6 != nullptr) {
		groupDelta6->startUpdate(0x1);

		groupMembers.set(0, newLeader, groupDelta6, 2);
		groupMembers.set(groupPosition, oldLeader.get(), groupDelta6, 0);

		groupDelta6->close();
		broadcastMessage(groupDelta6);
	}

	if (hasSquadLeader())
		addGroupModifiers();

	// Send out leader update message
	StringIdChatParameter message;
	message.setStringId("group", "new_leader"); // %TU is now the group leader.

	String firstNameLeader = newLeader->getFirstName();
	bool galaxyWide = ConfigManager::instance()->getBool("Core3.PlayerManager.GalaxyWideGrouping", false);

	if (galaxyWide) {
		message.setTU(newLeader->getDisplayedName());
	} else {
		message.setTU(newLeader->getObjectID());
	}

	for (int i = 0; i < groupMembers.size(); ++i) {
		CreatureObject* member = getGroupMember(i);

		if (member == nullptr || !member->isPlayerCreature())
			continue;

		member->sendSystemMessage(message);
	}
}

void GroupObjectImplementation::disband() {
	//Group is locked

	bool hasSL = hasSquadLeader();
	int groupSize = groupMembers.size();

	for (int i = groupSize - 1; i >= 0; --i) {
		ManagedReference<CreatureObject*> groupMember = getGroupMember(i);

		groupMembers.remove(i);

		if (groupMember == nullptr)
			continue;

		try {
			Locker clocker(groupMember, _this.getReferenceUnsafeStaticCast());

			if (groupMember->isPlayerCreature()) {
				PlayerObject* ghost = groupMember->getPlayerObject();

				if (ghost != nullptr) {
					ghost->removeWaypointBySpecialType(WaypointObject::SPECIALTYPE_NEARESTMISSIONFORGROUP);
				}

				if (hasSL)
					removeGroupModifiers(groupMember);
			}

			groupMember->updateGroup(nullptr);

			updatePvPStatusNearCreature(groupMember);

		} catch (Exception& e) {
			System::out << "Exception in GroupObject::disband(Player* player)\n";
		}
	}

	destroyChatRoom();
}

bool GroupObjectImplementation::hasSquadLeader() {
	Reference<CreatureObject*> leader = getLeader();

	if (leader == nullptr)
		return false;

	if (leader->isPlayerCreature() && leader->hasSkill("outdoors_squadleader_novice")) {
			return true;
	}

	return false;
}

void GroupObjectImplementation::addGroupModifiers() {
	ManagedReference<GroupObject*> thisGroup = _this.getReferenceUnsafeStaticCast();

	Locker glocker(thisGroup);

	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* player = getGroupMember(i);

		if (!player->isPlayerCreature())
			continue;

		Locker clocker(player, thisGroup);

		addGroupModifiers(player);
	}
}

void GroupObjectImplementation::removeGroupModifiers() {
	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* player = getGroupMember(i);

		if (!player->isPlayerCreature())
			continue;

		removeGroupModifiers(player);
	}
}

void GroupObjectImplementation::addGroupModifiers(CreatureObject* player) {
	if (player == nullptr)
		return;

	Reference<CreatureObject*> leader = getLeader();

	if (leader == nullptr)
		return;

	if (!leader->isPlayerCreature())
		return;

	int duration = 300;

	String action = "squadleader";

	if (player->hasBuff(action.hashCode()))
		player->removeBuff(action.hashCode());

	ManagedReference<SquadLeaderBuff*> buff = new SquadLeaderBuff(player, leader, action.hashCode(), duration);

	Locker locker(buff);

	buff->setSkillModifier("slope_move", leader->getSkillMod("group_slope_move"));
	buff->setSkillModifier("private_group_ranged_defense", leader->getSkillMod("group_ranged_defense"));
	buff->setSkillModifier("private_group_melee_defense", leader->getSkillMod("group_melee_defense"));
	buff->setSkillModifier("burst_run", leader->getSkillMod("group_burst_run"));
	player->addBuff(buff);

	buff->addObservers();
}

void GroupObjectImplementation::removeGroupModifiers(CreatureObject* player) {
	if (player == nullptr)
		return;

	Reference<CreatureObject*> leader = getLeader();

	if (leader == nullptr)
		return;

	if (!leader->isPlayerCreature())
		return;

	Locker clocker(player, _this.getReferenceUnsafeStaticCast());
	String action = "squadleader";

	if (player->hasBuff(action.hashCode()))
		player->removeBuff(action.hashCode());

	player->updateSpeedAndAccelerationMods();
}

float GroupObjectImplementation::getGroupHarvestModifier(CreatureObject* player) {

	String skillNovice = "outdoors_ranger_novice";
	String skillMaster = "outdoors_ranger_master";

	float modifier = 1.2f;

	for (int i = 0; i < groupMembers.size(); ++i) {
		Reference<CreatureObject*> groupMember = getGroupMember(i);

		if (groupMember->isPlayerCreature()) {

			if (groupMember == player)
				continue;

			if (groupMember->hasSkill(skillNovice)) {

				if (groupMember->isInRange(player, 64.0f)) {

					if (groupMember->hasSkill(skillMaster)) {
						modifier = 1.4f;
						break;
					}

					modifier = 1.3f;
				}
			}
		}
	}

	return modifier;
}

void GroupObjectImplementation::calculateGroupLevel() {
	int highestPlayer = 0;
	groupLevel = 0;
	factionPetLevel = 0;

	for (int i = 0; i < getGroupSize(); i++) {
		Reference<CreatureObject*> member = getGroupMember(i);

		if (member->isPet()) {
				ManagedReference<PetControlDevice*> pcd = member->getControlDevice().get().castTo<PetControlDevice*>();

				if (pcd != nullptr && pcd->getPetType() == PetManager::FACTIONPET) {
					factionPetLevel += member->getLevel() / 5;
				}

				groupLevel += member->getLevel() / 5;
		} else if (member->isPlayerCreature()) {
			int memberLevel = member->getLevel();

			if (memberLevel > highestPlayer) {
				groupLevel += (memberLevel - highestPlayer + (highestPlayer / 5));
				highestPlayer = memberLevel;
			} else {
				groupLevel += memberLevel / 5;
			}
		}
	}
}

int GroupObjectImplementation::getNumberOfPlayerMembers() {
	int playerCount = 0;

	for (int i = 0; i < getGroupSize(); i++) {
		Reference<CreatureObject*> member = getGroupMember(i);

		if (member->isPlayerCreature()) {
			playerCount++;
		}
	}

	return playerCount;
}

void GroupObjectImplementation::sendSystemMessage(StringIdChatParameter& param, bool sendLeader) {
	Locker lock(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < groupMembers.size(); ++i) {
		CreatureObject* member = getGroupMember(i);

		if (member == nullptr || !member->isPlayerCreature())
			continue;

		if (!sendLeader && member->getObjectID() == getLeaderID())
			continue;

		member->sendSystemMessage(param);
	}
}

void GroupObjectImplementation::sendSystemMessage(const String& fullPath, bool sendLeader) {
	Locker lock(_this.getReferenceUnsafeStaticCast());

	uint64 leaderID = getLeaderID();

	for (int i = 0; i < groupMembers.size(); ++i) {
		CreatureObject* member = getGroupMember(i);

		if (member == nullptr)
			continue;

		if (!member->isPlayerCreature() || (!sendLeader && member->getObjectID() == leaderID))
			continue;

		member->sendSystemMessage(fullPath);
	}
}

void GroupObjectImplementation::sendSystemMessage(StringIdChatParameter& param, CreatureObject* excluded) {
	Locker lock(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < groupMembers.size(); ++i) {
		Reference<CreatureObject*> member = getGroupMember(i);

		if (member == nullptr || !member->isPlayerCreature() || member == excluded)
			continue;

		member->sendSystemMessage(param);
	}
}

bool GroupObjectImplementation::isOtherMemberPlayingMusic(CreatureObject* player) {
	if (player == nullptr)
		return false;

	uint64 playerID = player->getObjectID();

	for (int i = 0; i < getGroupSize(); ++i) {
		Reference<CreatureObject*> member = getGroupMember(i);

		if (member == nullptr || !member->isPlayerCreature())
			continue;

		if (member->getObjectID() == playerID || !member->isPlayingMusic())
			continue;

		return true;
	}

	return false;
}

void GroupObjectImplementation::scheduleUpdateNearestMissionForGroup(unsigned int planetCRC) {
	Reference<UpdateNearestMissionForGroupTask*> task = nullptr;

	if (updateNearestMissionForGroupTasks.contains(planetCRC)) {
		task = updateNearestMissionForGroupTasks.get(planetCRC);
		if (task == nullptr) {
			updateNearestMissionForGroupTasks.drop(planetCRC);
		}
	}

	if (task == nullptr) {
		task = new UpdateNearestMissionForGroupTask(_this.getReferenceUnsafeStaticCast(), planetCRC);
		updateNearestMissionForGroupTasks.put(planetCRC, task);
	}

	if (task->isScheduled()) {
		task->reschedule(10000);
	}
	else {
		task->schedule(10000);
	}
}

void GroupObjectImplementation::updateLootRules() {
	GroupObjectDeltaMessage6* msg = new GroupObjectDeltaMessage6(_this.getReferenceUnsafeStaticCast());
	msg->updateLootRules(this->masterLooterID, this->lootRule);
	msg->close();

	broadcastMessage(msg);
}

bool GroupObjectImplementation::initializeLeader(CreatureObject* leader, CreatureObject* member) {
	if (leader == nullptr || member == nullptr)
		return false;

	groupMembers.add(leader, nullptr);
	groupMembers.add(member, nullptr, 0);

	setMasterLooterID(leader->getObjectID());
	setLootRule(GroupManager::FREEFORALL);
	calculateGroupLevel();

#ifdef DEBUG_GROUPS
	info(true) << "Initialize Leader called for Leader: " << leader->getDisplayedName() << " with Initial Member: " << member->getDisplayedName();
#endif

	return true;
}

uint64 GroupObjectImplementation::getLeaderID() {
	if (groupMembers.size() == 0)
		return 0;

	CreatureObject* leader = getLeader();

	if (leader == nullptr)
		return 0;

	return leader->getObjectID();
}
