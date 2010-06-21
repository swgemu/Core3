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
#include "server/zone/ZoneProcessServerImplementation.h"
#include "server/zone/ZoneServer.h"
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

void GroupObjectImplementation::addMember(SceneObject* player) {
	GroupObjectDeltaMessage6* grp = new GroupObjectDeltaMessage6((GroupObject*) _this);
	grp->startUpdate(1);
	groupMembers.add(player, grp);
	grp->close();

	broadcastMessage(grp);

	sendTo(player, true);
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

			CreatureObject* crea = (CreatureObject*)scno;
			try {
				/*********** for training ************/
				crea->wlock();
				//TODO: Does this need a lock for the other student/teacher?

				if (crea->isPlayerCreature() ) {

					PlayerCreature* play = (PlayerCreature*) crea;

					if (play->getTeacher() != NULL) {

						//if play is the teacher then we want to grab a reference before we set student = NULL
						if (play->getStudent() != NULL) {

							play->getStudent()->setTeacher(NULL);
							play->setStudent(NULL);
						}

						play->getTeacher()->setStudent(NULL);
						play->setTeacher(NULL);

					}

					//usually not going to need this one but this will be a failsafe in case something weird happens
					if (play->getStudent() != NULL) {

						if(play->getTeacher() != NULL) {

							play->getTeacher()->setStudent(NULL);
							play->setTeacher(NULL);
						}

						play->getStudent()->setTeacher(NULL);
						play->setStudent(NULL);

					}

				}

				crea->unlock();
				/********************************/

				return;
			} catch (...) {
				crea->unlock();
			}
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
		CreatureObject* crea = (CreatureObject*) ( (SceneObject*) groupMembers.get(i) );
		try {
			crea->wlock((GroupObject*) _this);

			if (crea->isPlayerCreature()) {

				PlayerCreature* play = (PlayerCreature*) crea;

				chatRoom->removePlayer((PlayerCreature*) play, false);
				chatRoom->sendDestroyTo((PlayerCreature*) play);

				ChatRoom* room = chatRoom->getParent();
				room->sendDestroyTo((PlayerCreature*) play);

				play->updateGroup(NULL);
				//play->updateGroupId(0);

				if (play->getTeacher() != NULL) {

					//if play is the teacher then we want to grab a reference before we set student = NULL
					if(play->getStudent() != NULL) {
						play->getStudent()->setTeacher(NULL);
						play->setStudent(NULL);
					}

					play->getTeacher()->setStudent(NULL);
					play->setTeacher(NULL);

				}

				//usually not going to need this one but this will be a failsafe in case something weird happens
				if (play->getStudent() != NULL) {

					if(play->getTeacher() != NULL) {
						play->getTeacher()->setStudent(NULL);
						play->setTeacher(NULL);
					}

					play->getStudent()->setTeacher(NULL);
					play->setStudent(NULL);

				}

			}

			//sendClosestWaypointDestroyTo(play);

			//removeSquadLeaderBonuses(play);

			sendDestroyTo(crea);

			crea->unlock();

		} catch (...) {
			System::out << "Exception in GroupObject::disband(Player* player)\n";
			crea->unlock();
		}
	}

	destroyChatRoom();

	groupMembers.removeAll();

	//The mission waypoints should not be destroyed. They belong to the players.
	//missionWaypoints.removeAll();
}

