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
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/objects/group/RemovePetsFromGroupTask.h"
#include "server/zone/objects/group/tasks/UpdateNearestMissionForGroupTask.h"
#include "server/zone/managers/mission/MissionManager.h"
#include "server/zone/objects/waypoint/WaypointObject.h"

void GroupObjectImplementation::sendBaselinesTo(SceneObject* player) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	BaseMessage* grup3 = new GroupObjectMessage3(_this.getReferenceUnsafeStaticCast());
	client->sendMessage(grup3);

	BaseMessage* grup6 = new GroupObjectMessage6(_this.getReferenceUnsafeStaticCast());
	client->sendMessage(grup6);

	if (player->isPlayerCreature() && chatRoom != NULL)
		chatRoom->sendTo(cast<CreatureObject*>( player));
}

void GroupObjectImplementation::startChatRoom() {
	Reference<CreatureObject*> leader = groupMembers.get(0).get().castTo<CreatureObject*>();
	ChatManager* chatManager = server->getZoneServer()->getChatManager();

	chatRoom = chatManager->createGroupRoom(getObjectID(), leader);
}

void GroupObjectImplementation::destroyChatRoom() {
	if (chatRoom == NULL)
		return;

	ManagedReference<ChatRoom*> room = chatRoom->getParent();
	ManagedReference<ChatRoom*> parent = room->getParent();

	ChatManager* chatManager = server->getZoneServer()->getChatManager();

	chatManager->destroyRoom(chatRoom);
	chatManager->destroyRoom(room);

	chatRoom = NULL;
}

void GroupObjectImplementation::broadcastMessage(BaseMessage* msg) {
	for (int i = 0; i < groupMembers.size(); i++) {
		SceneObject* member = groupMembers.get(i).get().get();

		if (member->isPlayerCreature())
			member->sendMessage(msg->clone());
	}

	delete msg;
}

void GroupObjectImplementation::broadcastMessage(CreatureObject* player, BaseMessage* msg, bool sendSelf) {
	for (int i = 0; i < groupMembers.size(); i++) {
		SceneObject* member = groupMembers.get(i).get().get();

		if(!sendSelf && member == player)
			continue;

		if (member->isPlayerCreature())
			member->sendMessage(msg->clone());
	}

	delete msg;
}

void GroupObjectImplementation::addMember(SceneObject* newMember) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	GroupObjectDeltaMessage6* grp = new GroupObjectDeltaMessage6(_this.getReferenceUnsafeStaticCast());
	grp->startUpdate(1);
	groupMembers.add(newMember, grp);
	grp->close();

	broadcastMessage(grp);

	if (newMember->isPlayerCreature())
	{
		ManagedReference<CreatureObject*> playerCreature = cast<CreatureObject*>(newMember);

		sendTo(playerCreature, true);

		if (hasSquadLeader()) {
			addGroupModifiers(playerCreature);
		}

		scheduleUpdateNearestMissionForGroup(playerCreature->getPlanetCRC());
	}

	calcGroupLevel();
}

void GroupObjectImplementation::removeMember(SceneObject* member) {
	ManagedReference<SceneObject*> obj = member;

	for (int i = 0; i < groupMembers.size(); i++) {
		SceneObject* scno = groupMembers.get(i).get().get();

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
		CreatureObject* playerCreature = cast<CreatureObject*>(member);
		RemovePetsFromGroupTask* task = new RemovePetsFromGroupTask(playerCreature, _this.getReferenceUnsafeStaticCast());
		task->execute();

		//Close any open Group SUIs.
		ManagedReference<PlayerObject*> ghost = playerCreature->getPlayerObject();
		if (ghost != NULL) {
			ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_RULE);
			ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_CHANGED);
			ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_PICK_LOOTER);
		}

		//Reset Master Looter if needed.
		if (getMasterLooterID() == playerCreature->getObjectID()) {
			ManagedReference<CreatureObject*> groupLeader = (getLeader()).castTo<CreatureObject*>();
			GroupManager::instance()->changeMasterLooter(_this.getReferenceUnsafeStaticCast(), groupLeader, false);
		}

		if (hasSquadLeader()) {
			removeGroupModifiers(playerCreature);
		}

		if (playerCreature->getPlayerObject() != NULL) {
			PlayerObject* ghost = playerCreature->getPlayerObject();
			ghost->removeWaypointBySpecialType(WaypointObject::SPECIALTYPE_NEARESTMISSIONFORGROUP);
		}
		scheduleUpdateNearestMissionForGroup(playerCreature->getPlanetCRC());
	}

	calcGroupLevel();
}

bool GroupObjectImplementation::hasMember(SceneObject* member) {
	for (int i = 0; i < groupMembers.size(); i++) {
		SceneObject* play = groupMembers.get(i).get().get();

		if (play == member)
			return true;
	}

	return false;
}

bool GroupObjectImplementation::hasMember(uint64 member) {
	for (int i = 0; i < groupMembers.size(); i++) {
		SceneObject* play = groupMembers.get(i).get().get();

		if (play->getObjectID() == member)
			return true;
	}

	return false;
}

void GroupObjectImplementation::makeLeader(SceneObject* player) {
	if (groupMembers.size() < 2 || !player->isPlayerCreature())
		return;

	//SceneObject* obj = groupMembers.get();

	Reference<SceneObject*> temp = groupMembers.get(0).get();

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
	// this locked
	ManagedReference<ChatRoom* > chat = chatRoom;

	for (int i = 0; i < groupMembers.size(); i++) {
		if (groupMembers.get(i) == NULL) {
			continue;
		}

		Reference<CreatureObject*> groupMember = getGroupMember(i).castTo<CreatureObject*>();

		try {
			Locker clocker(groupMember, _this.getReferenceUnsafeStaticCast());

			if (groupMember->isPlayerCreature()) {
				if (chat != NULL) {
					chat->removePlayer(groupMember, false);
					chat->sendDestroyTo(groupMember);

					ChatRoom* room = chat->getParent();
					room->sendDestroyTo(groupMember);
				}

				if (groupMember->getPlayerObject() != NULL) {
					PlayerObject* ghost = groupMember->getPlayerObject();
					ghost->removeWaypointBySpecialType(WaypointObject::SPECIALTYPE_NEARESTMISSIONFORGROUP);
				}
			}

			groupMember->updateGroup(NULL);
			//play->updateGroupId(0);

			//sendClosestWaypointDestroyTo(play);

			//removeSquadLeaderBonuses(play);
		} catch (Exception& e) {
			System::out << "Exception in GroupObject::disband(Player* player)\n";
		}
	}

	destroyChatRoom();

	if (hasSquadLeader())
		removeGroupModifiers();

	groupMembers.removeAll();

	//The mission waypoints should not be destroyed. They belong to the players.
	//missionWaypoints.removeAll();
}

bool GroupObjectImplementation::hasSquadLeader() {
	if (getLeader() == NULL)
		return false;

	if (getLeader()->isPlayerCreature()) {
		Reference<CreatureObject*> leader = getLeader().castTo<CreatureObject*>();

		if (leader->hasSkill("outdoors_squadleader_novice"))
			return true;
	}

	return false;
}

void GroupObjectImplementation::addGroupModifiers() {
	ManagedReference<GroupObject*> thisGroup = _this.getReferenceUnsafeStaticCast();

	Locker glocker(thisGroup);

	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* crea = getGroupMember(i).castTo<CreatureObject*>().get();

		if (crea == NULL)
			continue;

		if (!crea->isPlayerCreature())
			continue;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( crea);

		Locker clocker(player, thisGroup);

		addGroupModifiers(player);
	}
}

void GroupObjectImplementation::removeGroupModifiers() {
	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* crea = getGroupMember(i).castTo<CreatureObject*>().get();

		if (crea == NULL)
			continue;

		if (!crea->isPlayerCreature())
			continue;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>( crea);
		removeGroupModifiers(player);
	}
}

void GroupObjectImplementation::addGroupModifiers(CreatureObject* player) {
	if (player == NULL)
		return;

	if (getLeader() == NULL)
		return;

	if (!getLeader()->isPlayerCreature())
		return;

	Reference<CreatureObject*> leader = getLeader().castTo<CreatureObject*>();

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
}

void GroupObjectImplementation::removeGroupModifiers(CreatureObject* player) {
	if (player == NULL)
		return;

	if (getLeader() == NULL)
		return;

	if (!getLeader()->isPlayerCreature())
		return;

	Reference<CreatureObject*> leader = ( getLeader()).castTo<CreatureObject*>();

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

	for(int i = 0; i < groupMembers.size(); ++i) {
		Reference<SceneObject*> scno = getGroupMember(i);

		if(scno->isPlayerCreature()) {
			CreatureObject* groupMember = cast<CreatureObject*>( scno.get());

			if(groupMember == player)
				continue;

			if(groupMember->hasSkill(skillNovice)) {

				if(groupMember->isInRange(player, 64.0f)) {

					if(groupMember->hasSkill(skillMaster)) {
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
	groupLevel = 0;

	for (int i = 0; i < getGroupSize(); i++) {
		SceneObject* member = getGroupMember(i);

		if (member->isCreatureObject()) {
			CreatureObject* creature = cast<CreatureObject*>(member);

			int currentlevel = groupLevel - getGroupSize();
			int memberlevel = creature->getLevel();

			if (memberlevel > currentlevel)
				groupLevel = memberlevel + getGroupSize();
		}
	}

	GroupObjectDeltaMessage6* msg = new GroupObjectDeltaMessage6(_this.getReferenceUnsafeStaticCast());

	msg->updateLevel(this->groupLevel);
	msg->close();

	broadcastMessage(msg);
}

void GroupObjectImplementation::sendSystemMessage(StringIdChatParameter& param, bool sendLeader) {
	Locker lock(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < groupMembers.size(); ++i) {
		GroupMember* member = &groupMembers.get(i);

		ManagedReference<SceneObject*> obj = member->get();

		if (obj == NULL || !obj->isPlayerCreature() || (!sendLeader && obj == getLeader()))
			continue;

		CreatureObject* creature = cast<CreatureObject*>(obj.get());
		creature->sendSystemMessage(param);
	}
}

void GroupObjectImplementation::sendSystemMessage(const String& fullPath, bool sendLeader) {
	Locker lock(_this.getReferenceUnsafeStaticCast());

	for (int i = 0; i < groupMembers.size(); ++i) {
		GroupMember* member = &groupMembers.get(i);

		ManagedReference<SceneObject*> obj = member->get();

		if (obj == NULL || !obj->isPlayerCreature() || (!sendLeader && obj == getLeader()))
			continue;

		CreatureObject* creature = cast<CreatureObject*>(obj.get());
		creature->sendSystemMessage(fullPath);
	}
}

bool GroupObjectImplementation::isOtherMemberPlayingMusic(CreatureObject* player) {
	for (int i = 0; i < getGroupSize(); ++i) {
		Reference<CreatureObject*> groupMember = (getGroupMember(i)).castTo<CreatureObject*>();

		if (groupMember == NULL || groupMember == player || !groupMember->isPlayerCreature())
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
