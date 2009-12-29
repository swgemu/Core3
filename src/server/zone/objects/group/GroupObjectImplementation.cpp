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
#include "server/zone/objects/creature/CreatureObject.h"

void GroupObjectImplementation::sendBaselinesTo(SceneObject* player) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	BaseMessage* grup3 = new GroupObjectMessage3((GroupObject*) _this);
	client->sendMessage(grup3);

	BaseMessage* grup6 = new GroupObjectMessage6((GroupObject*) _this);
	client->sendMessage(grup6);

	if (player->isPlayerCreature() && groupChannel != NULL)
		groupChannel->sendTo((PlayerCreature*)player);
}

void GroupObjectImplementation::startChannel() {
	groupChannel = NULL;
}

void GroupObjectImplementation::broadcastMessage(BaseMessage* msg) {
	for (int i = 0; i < groupMembers.size(); i++) {
		SceneObject* play = groupMembers.get(i);

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

	sendTo(player);
}

void GroupObjectImplementation::removeMember(SceneObject* player) {
	ManagedReference<SceneObject*> obj = player;

	for (int i = 0; i < groupMembers.size(); i++) {
		SceneObject* play = groupMembers.get(i);

		if (play == player) {
			GroupObjectDeltaMessage6* grp = new GroupObjectDeltaMessage6((GroupObject*) _this);
			grp->startUpdate(1);
			groupMembers.remove(i, grp);
			grp->close();

			broadcastMessage(grp);

			return;
		}
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

			groupMembers.set(0, player, grp, 2);
			groupMembers.set(i, temp.get(), grp, 0);

			grp->close();

			broadcastMessage(grp);

			return;
		}
	}
}

void GroupObjectImplementation::disband() {
	// this locked
	for (int i = 0; i < groupMembers.size(); i++) {
		CreatureObject* play = (CreatureObject*) ( (SceneObject*) groupMembers.get(i) );
		try {
			play->wlock((GroupObject*) _this);

			//play->removeChatRoom(groupChannel);

			//sendClosestWaypointDestroyTo(play);

			play->updateGroup(NULL);
			//play->updateGroupId(0);

			/*if (play->getTeacher() != NULL) {
				play->getTeacher()->setStudent(NULL);
				play->setTeacher(NULL);
			}

			if (play->getStudent() != NULL) {
				play->getStudent()->setTeacher(NULL);
				play->setStudent(NULL);
			}*/

			//removeSquadLeaderBonuses(play);

			sendDestroyTo(play);

			play->unlock();

		} catch (...) {
			System::out << "Exception in GroupObject::disband(Player* player)\n";
			play->unlock();
		}
	}

	/*

	if (groupChannel != NULL) {
		ChatRoom* room = groupChannel->getParent();
		ChatRoom* parent = room->getParent();

		ChatManager* chatManager = getZone()->getChatManager();

		chatManager->destroyRoom(groupChannel);
		chatManager->destroyRoom(room);

		groupChannel = NULL;
	}*/

	groupMembers.removeAll();

	//The mission waypoints should not be destroyed. They belong to the players.
	//missionWaypoints.removeAll();
}

