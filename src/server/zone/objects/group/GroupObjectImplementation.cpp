/*
 * GroupObjectImplementation.cpp
 *
 *  Created on: 29/12/2009
 *      Author: victor
 */

#include "GroupObject.h"
#include "server/zone/packets/group/GroupObjectMessage3.h"
#include "server/zone/packets/group/GroupObjectMessage6.h"
#include "server/zone/packets/group/GroupObjectDeltaMessage6.h"
#include "server/zone/ZoneClientSession.h"
#include "server/chat/room/ChatRoom.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/player/events/SquadLeaderBonusTask.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

void GroupObjectImplementation::sendBaselinesTo(SceneObject* player) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	BaseMessage* grup3 = new GroupObjectMessage3((GroupObject*) _this);
	client->sendMessage(grup3);

	BaseMessage* grup6 = new GroupObjectMessage6((GroupObject*) _this);
	client->sendMessage(grup6);

	if (player->isPlayerCreature() && chatRoom != NULL)
		chatRoom->sendTo((PlayerCreature*) player);
}

void GroupObjectImplementation::startChatRoom() {
	PlayerCreature* leader = (PlayerCreature*) ((SceneObject*) groupMembers.get(0));
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
		SceneObject* play = groupMembers.get(i);

		play->sendMessage(msg->clone());
	}

	delete msg;
}

void GroupObjectImplementation::broadcastMessage(PlayerCreature* player, BaseMessage* msg, bool sendSelf) {
	for (int i = 0; i < groupMembers.size(); i++) {
		SceneObject* play = groupMembers.get(i);

		if(!sendSelf && play == player)
			continue;

		play->sendMessage(msg->clone());
	}

	delete msg;
}

void GroupObjectImplementation::addMember(SceneObject* player) {
	GroupObjectDeltaMessage6* grp = new GroupObjectDeltaMessage6((GroupObject*) _this);
	grp->startUpdate(1);
	groupMembers.add(player, grp);
	grp->close();

	broadcastMessage(grp);

	sendTo(player, true);

	if (hasSquadLeader() && player->isPlayerCreature()) {
		ManagedReference<PlayerCreature*> playerCreature = (PlayerCreature*) player;
		addGroupModifiers(playerCreature);
	}
}

void GroupObjectImplementation::removeMember(SceneObject* player) {
	ManagedReference<SceneObject*> obj = player;

	for (int i = 0; i < groupMembers.size(); i++) {
		SceneObject* scno = groupMembers.get(i);

		if (scno == player) {
			GroupObjectDeltaMessage6* grp = new GroupObjectDeltaMessage6((GroupObject*) _this);
			grp->startUpdate(1);
			groupMembers.remove(i, grp);
			grp->close();

			broadcastMessage(grp);
		}
	}

	if (hasSquadLeader() && player->isPlayerCreature()) {
		ManagedReference<PlayerCreature*> playerCreature = (PlayerCreature*) player;
		removeGroupModifiers(playerCreature);
	}
}

bool GroupObjectImplementation::hasMember(SceneObject* player) {
	for (int i = 0; i < groupMembers.size(); i++) {
		SceneObject* play = groupMembers.get(i);

		if (play == player)
			return true;
	}

	return false;
}


void GroupObjectImplementation::makeLeader(SceneObject* player) {
	if (groupMembers.size() < 2)
		return;

	//SceneObject* obj = groupMembers.get();

	ManagedReference<SceneObject*> temp = (SceneObject*) groupMembers.get(0);

	for (int i = 0; i < groupMembers.size(); ++i) {
		if (groupMembers.get(i) == player) {
			GroupObjectDeltaMessage6* grp = new GroupObjectDeltaMessage6((GroupObject*) _this);
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
	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* crea = (CreatureObject*) ( (SceneObject*) groupMembers.get(i) );
		try {
			Locker clocker(crea, _this);


			if (crea->isPlayerCreature()) {

				PlayerCreature* play = (PlayerCreature*) crea;

				chatRoom->removePlayer((PlayerCreature*) play, false);
				chatRoom->sendDestroyTo((PlayerCreature*) play);

				ChatRoom* room = chatRoom->getParent();
				room->sendDestroyTo((PlayerCreature*) play);

				play->updateGroup(NULL);
				//play->updateGroupId(0);

			}

			//sendClosestWaypointDestroyTo(play);

			//removeSquadLeaderBonuses(play);

			sendDestroyTo(crea);

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

		ManagedReference<PlayerCreature*> leader = (PlayerCreature*) getLeader();

		if (leader->hasSkillBox("outdoors_squadleader_novice"))
			return true;
	}

	return false;
}

void GroupObjectImplementation::addGroupModifiers() {
	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* crea = (CreatureObject*) ( (SceneObject*) groupMembers.get(i) );

		if (crea == NULL)
			continue;

		if (!crea->isPlayerCreature())
			continue;

		ManagedReference<PlayerCreature*> player = (PlayerCreature*) crea;
		addGroupModifiers(player);
	}

	if (getLeader() != NULL) {
		if (getLeader()->isPlayerCreature()) {

			ManagedReference<PlayerCreature*> leader = (PlayerCreature*) getLeader();

			Reference<SquadLeaderBonusTask*> bonusTask = new SquadLeaderBonusTask(leader);

			bonusTask->schedule(300 * 1000);
		}
	}
}

void GroupObjectImplementation::removeGroupModifiers() {
	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* crea = (CreatureObject*) ( (SceneObject*) groupMembers.get(i) );

		if (crea == NULL)
			continue;

		if (!crea->isPlayerCreature())
			continue;

		ManagedReference<PlayerCreature*> player = (PlayerCreature*) crea;
		removeGroupModifiers(player);
	}
}

void GroupObjectImplementation::addGroupModifiers(PlayerCreature* player) {
	if (player == NULL)
		return;

	if (getLeader() == NULL)
		return;

	if (!getLeader()->isPlayerCreature())
		return;

	ManagedReference<PlayerCreature*> leader = (PlayerCreature*) getLeader();

	if (leader == player)
		return;

	Locker locker(player);

	int duration = 300;

	String action = "squadleader";

	if (player->hasBuff(action.hashCode()))
		player->removeBuff(action.hashCode());

	ManagedReference<Buff*> buff = new Buff(player, action.hashCode(), duration, BuffType::SKILL);
	buff->setSkillModifier("slope_move", leader->getSkillMod("group_slope_move"));
	buff->setSkillModifier("ranged_defense", leader->getSkillMod("group_ranged_defense"));
	buff->setSkillModifier("melee_defense", leader->getSkillMod("group_melee_defense"));
	buff->setSkillModifier("burst_run", leader->getSkillMod("group_burst_run"));

	player->addBuff(buff);
}

void GroupObjectImplementation::removeGroupModifiers(PlayerCreature* player) {
	if (player == NULL)
		return;

	if (getLeader() == NULL)
		return;

	if (!getLeader()->isPlayerCreature())
		return;

	ManagedReference<PlayerCreature*> leader = (PlayerCreature*) getLeader();

	if (leader == player)
		return;

	Locker locker(player);
	String action = "squadleader";

	if (player->hasBuff(action.hashCode()))
		player->removeBuff(action.hashCode());
}

float GroupObjectImplementation::getGroupHarvestModifier(PlayerCreature* player) {

	String skillNovice = "outdoors_ranger_novice";
	String skillMaster = "outdoors_ranger_master";

	float modifier = 1.2f;

	for(int i = 0; i < groupMembers.size(); ++i) {
		ManagedReference<SceneObject*> scno = (SceneObject*)groupMembers.get(i);

		if(scno->isPlayerCreature()) {
			PlayerCreature* groupMember = (PlayerCreature*) scno.get();

			if(groupMember == player)
				continue;

			if(groupMember->hasSkillBox(skillNovice)) {

				if(groupMember->isInRange(player, 64.0f)) {

					if(groupMember->hasSkillBox(skillMaster)) {
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
