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
#include "server/zone/objects/group/RemovePetsFromGroupTask.h"
#include "server/zone/objects/group/tasks/UpdateNearestMissionForGroupTask.h"
#include "server/zone/objects/waypoint/WaypointObject.h"

void GroupObjectImplementation::sendBaselinesTo(SceneObject* player) {
	auto client = player->getClient();
	if (client == NULL)
		return;

	BaseMessage* grup3 = new GroupObjectMessage3(_this.getReferenceUnsafeStaticCast());
	client->sendMessage(grup3);

	BaseMessage* grup6 = new GroupObjectMessage6(_this.getReferenceUnsafeStaticCast());
	client->sendMessage(grup6);

	if (player->isPlayerCreature() && chatRoom != NULL)
		chatRoom->sendTo(cast<CreatureObject*>( player));
}

void GroupObjectImplementation::startChatRoom(CreatureObject* leader) {
	ChatManager* chatManager = server->getZoneServer()->getChatManager();

	chatRoom = chatManager->createGroupRoom(getObjectID(), leader);
}

void GroupObjectImplementation::destroyChatRoom() {
	if (chatRoom == NULL)
		return;

	ChatManager* chatManager = server->getZoneServer()->getChatManager();
	ManagedReference<ChatRoom*> parent = chatRoom->getParent();

	chatManager->destroyRoom(chatRoom);

	if (parent != NULL)
		chatManager->destroyRoom(parent);

	chatRoom = NULL;
}

void GroupObjectImplementation::broadcastMessage(BaseMessage* msg) {
	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* member = groupMembers.get(i).get().get();

		if (member->isPlayerCreature())
			member->sendMessage(msg->clone());
	}

	delete msg;
}

void GroupObjectImplementation::broadcastMessage(CreatureObject* player, BaseMessage* msg, bool sendSelf) {
	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* member = groupMembers.get(i).get().get();

		if(!sendSelf && member == player)
			continue;

		if (member->isPlayerCreature())
			member->sendMessage(msg->clone());
	}

	delete msg;
}

void GroupObjectImplementation::updatePvPStatusNearCreature(CreatureObject* creature) {
	CloseObjectsVector* creatureCloseObjects = (CloseObjectsVector*) creature->getCloseObjects();
	SortedVector<QuadTreeEntry*> closeObjectsVector;

	creatureCloseObjects->safeCopyTo(closeObjectsVector);

	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* member = groupMembers.get(i).get().get();

		if (closeObjectsVector.contains(member)) {

			if (creature->isPlayerCreature())
				member->sendPvpStatusTo(creature);

			if (member->isPlayerCreature())
				creature->sendPvpStatusTo(member);
		}
	}
}

void GroupObjectImplementation::addMember(CreatureObject* newMember) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	GroupObjectDeltaMessage6* grp = new GroupObjectDeltaMessage6(_this.getReferenceUnsafeStaticCast());
	grp->startUpdate(1);
	groupMembers.add(newMember, grp);
	grp->close();

	broadcastMessage(grp);

	if (newMember->isPlayerCreature()) {
		sendTo(newMember, true);

		if (hasSquadLeader()) {
			addGroupModifiers(newMember);
		}

		scheduleUpdateNearestMissionForGroup(newMember->getPlanetCRC());
	}

	updatePvPStatusNearCreature(newMember);

	calcGroupLevel();
}

void GroupObjectImplementation::removeMember(CreatureObject* member) {
	bool wasLeader = getLeader() == member;

	if (hasSquadLeader()) {
		if (wasLeader)
			removeGroupModifiers();
		else
			removeGroupModifiers(member);
	}

	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* scno = groupMembers.get(i).get().get();

		if (scno == member) {
			GroupObjectDeltaMessage6* grp = new GroupObjectDeltaMessage6(_this.getReferenceUnsafeStaticCast());
			grp->startUpdate(1);
			groupMembers.remove(i, grp);
			grp->close();

			broadcastMessage(grp);
		}
	}

	if (member->isPlayerCreature()) {
		// Remove member's pets
		RemovePetsFromGroupTask* task = new RemovePetsFromGroupTask(member, _this.getReferenceUnsafeStaticCast());
		task->execute();

		//Close any open Group SUIs.
		ManagedReference<PlayerObject*> ghost = member->getPlayerObject();
		if (ghost != NULL) {
			ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_RULE);
			ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_CHANGED);
			ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_PICK_LOOTER);

			ghost->removeWaypointBySpecialType(WaypointObject::SPECIALTYPE_NEARESTMISSIONFORGROUP);
		}

		//Reset Master Looter if needed.
		if (getMasterLooterID() == member->getObjectID()) {
			ManagedReference<CreatureObject*> groupLeader = getLeader();
			GroupManager::instance()->changeMasterLooter(_this.getReferenceUnsafeStaticCast(), groupLeader, false);
		}

		if (wasLeader && hasSquadLeader()) {
			addGroupModifiers();
		}

		Zone* zone = member->getZone();

		if (zone != NULL) {
			scheduleUpdateNearestMissionForGroup(zone->getPlanetCRC());
		}
	}

	updatePvPStatusNearCreature(member);

	calcGroupLevel();
}

bool GroupObjectImplementation::hasMember(CreatureObject* member) {
	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* play = groupMembers.get(i).get().get();

		if (play == member)
			return true;
	}

	return false;
}

bool GroupObjectImplementation::hasMember(uint64 member) {
	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* play = groupMembers.get(i).get().get();

		if (play->getObjectID() == member)
			return true;
	}

	return false;
}

void GroupObjectImplementation::makeLeader(CreatureObject* player) {
	if (groupMembers.size() < 2 || !player->isPlayerCreature())
		return;

	Reference<CreatureObject*> temp = groupMembers.get(0).get();

	for (int i = 0; i < groupMembers.size(); ++i) {
		if (groupMembers.get(i) == player) {
			GroupObjectDeltaMessage6* grp = new GroupObjectDeltaMessage6(_this.getReferenceUnsafeStaticCast());
			grp->startUpdate(1);

			if (hasSquadLeader())
				removeGroupModifiers();

			groupMembers.set(0, player, grp, 2);
			groupMembers.set(i, temp.get(), grp, 0);

			grp->close();

			broadcastMessage(grp);

			if (hasSquadLeader())
				addGroupModifiers();

			return;
		}
	}
}

void GroupObjectImplementation::disband() {
	//Group is locked

	for (int i = 0; i < groupMembers.size(); i++) {
		if (groupMembers.get(i) == NULL)
			continue;

		Reference<CreatureObject*> groupMember = getGroupMember(i);

		try {
			Locker clocker(groupMember, _this.getReferenceUnsafeStaticCast());

			if (groupMember->isPlayerCreature()) {
				PlayerObject* ghost = groupMember->getPlayerObject();

				if (ghost != NULL) {
					ghost->removeWaypointBySpecialType(WaypointObject::SPECIALTYPE_NEARESTMISSIONFORGROUP);
				}
			}

			groupMember->updateGroup(NULL);

		} catch (Exception& e) {
			System::out << "Exception in GroupObject::disband(Player* player)\n";
		}
	}

	if (hasSquadLeader())
		removeGroupModifiers();

	while (groupMembers.size() > 0) {
		CreatureObject* member = groupMembers.get(0).get().get();

		updatePvPStatusNearCreature(member);

		groupMembers.remove(0);
	}

	destroyChatRoom();
}

bool GroupObjectImplementation::hasSquadLeader() {
	Reference<CreatureObject*> leader = getLeader();

	if (leader == NULL)
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
	if (player == NULL)
		return;

	Reference<CreatureObject*> leader = getLeader();

	if (leader == NULL)
		return;

	if (!leader->isPlayerCreature())
		return;

	if (leader == player)
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
	if (player == NULL)
		return;

	Reference<CreatureObject*> leader = getLeader();

	if (leader == NULL)
		return;

	if (!leader->isPlayerCreature())
		return;

	if (leader == player)
		return;

	Locker clocker(player, _this.getReferenceUnsafeStaticCast());
	String action = "squadleader";

	if (player->hasBuff(action.hashCode()))
		player->removeBuff(action.hashCode());

	player->updateTerrainNegotiation();
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

void GroupObjectImplementation::calcGroupLevel() {
	int highestPlayer = 0;
	groupLevel = 0;

	for (int i = 0; i < getGroupSize(); i++) {
		Reference<CreatureObject*> member = getGroupMember(i);

		if (member->isPet()) {
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

	GroupObjectDeltaMessage6* msg = new GroupObjectDeltaMessage6(_this.getReferenceUnsafeStaticCast());

	msg->updateLevel(this->groupLevel);
	msg->close();

	broadcastMessage(msg);
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
		CreatureObject* member = groupMembers.get(i).get().get();

		if (!member->isPlayerCreature() || (!sendLeader && member == getLeader()))
			continue;

		member->sendSystemMessage(param);
	}
}

void GroupObjectImplementation::sendSystemMessage(const String& fullPath, bool sendLeader) {
	Locker lock(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < groupMembers.size(); ++i) {
		CreatureObject* member = groupMembers.get(i).get().get();

		if (!member->isPlayerCreature() || (!sendLeader && member == getLeader()))
			continue;

		member->sendSystemMessage(fullPath);
	}
}

void GroupObjectImplementation::sendSystemMessage(StringIdChatParameter& param, CreatureObject* excluded) {
	Locker lock(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < groupMembers.size(); ++i) {
		CreatureObject* member = groupMembers.get(i).get().get();

		if (!member->isPlayerCreature() || member == excluded)
			continue;

		member->sendSystemMessage(param);
	}
}

bool GroupObjectImplementation::isOtherMemberPlayingMusic(CreatureObject* player) {
	for (int i = 0; i < getGroupSize(); ++i) {
		Reference<CreatureObject*> groupMember = getGroupMember(i);

		if (groupMember == player || !groupMember->isPlayerCreature())
			continue;

		if (groupMember->isPlayingMusic()) {
			return true;
		}
	}

	return false;
}

void GroupObjectImplementation::scheduleUpdateNearestMissionForGroup(unsigned int planetCRC) {
	Reference<UpdateNearestMissionForGroupTask*> task = NULL;

	if (updateNearestMissionForGroupTasks.contains(planetCRC)) {
		task = updateNearestMissionForGroupTasks.get(planetCRC);
		if (task == NULL) {
			updateNearestMissionForGroupTasks.drop(planetCRC);
		}
	}

	if (task == NULL) {
		task = new UpdateNearestMissionForGroupTask(_this.getReferenceUnsafeStaticCast(), planetCRC);
		updateNearestMissionForGroupTasks.put(planetCRC, task);
	}

	if (task->isScheduled()) {
		task->reschedule(30000);
	}
	else {
		task->schedule(30000);
	}
}

void GroupObjectImplementation::updateLootRules() {
	GroupObjectDeltaMessage6* msg = new GroupObjectDeltaMessage6(_this.getReferenceUnsafeStaticCast());
	msg->updateLootRules(this->masterLooterID, this->lootRule);
	msg->close();
	broadcastMessage(msg);
}
