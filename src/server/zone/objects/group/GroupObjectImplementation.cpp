/*
 * GroupObjectImplementation.cpp
 *
 *  Created on: 10/08/2009
 *      Author: victor
 */


#include "GroupObject.h"
#include "server/zone/packets/group/GroupObjectMessage3.h"
#include "server/zone/packets/group/GroupObjectMessage6.h"
#include "server/zone/packets/group/GroupObjectDeltaMessage6.h"

#include "server/zone/objects/player/PlayerCreature.h"

GroupObjectImplementation::GroupObjectImplementation(LuaObject* templateData) : SceneObjectImplementation(templateData) {
	setLoggingName("GroupObject");

	leader = NULL;
	groupMembers = new Vector<SceneObject*>();

	listCount = 0;

	groupLevel = 0;
}

void GroupObjectImplementation::sendTo(SceneObject* player) {
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

void GroupObjectImplementation::addPlayer(SceneObject* player) {
	int index = groupMembers.size();

	groupMembers->add(player);
	calcGroupLevel();
	addSquadLeaderBonuses(player);

	GroupObjectDeltaMessage6* grp = new GroupObjectDeltaMessage6((GroupObject*) _this);
	grp->addMember(player, index);
	grp->updateLevel(groupLevel);
	grp->close();

	broadcastMessage(grp);

	//groupMembers.add(player);
	//calcGroupLevel();

	sendTo(player);
}

void GroupObjectImplementation::calcGroupLevel() {
	groupLevel = 0;

	for (int i = 0; i < getGroupSize(); i++) {
		SceneObject* member = getGroupMember(i);

		if (member->isCreatureObject()) {
			CreatureObject* creature = (CreatureObject*) member;

			int currentlevel = groupLevel - getGroupSize();
			int memberlevel = creature->getLevel();

			if (memberlevel > currentlevel)
				groupLevel = memberlevel + getGroupSize();
		}
	}
}

void GroupObjectImplementation::removePlayer(SceneObject* player) {
	int size = groupMembers->size();

	for (int i = 0; i < size; i++) {
		SceneObject* play = groupMembers->get(i);

		if (play == player) {
			groupMembers->remove(i);

			calcGroupLevel();
			removeSquadLeaderBonuses(play);

			GroupObjectDeltaMessage6* grp = new GroupObjectDeltaMessage6((GroupObject*) _this);
			grp->removeMember(i);
			grp->updateLevel(groupLevel);
			grp->close();

			broadcastMessage(grp);

			break;
		}
	}

	if ((player == leader) && groupMembers->size() > 0)
		leader = groupMembers->get(0);

	calcGroupLevel();
}

bool GroupObjectImplementation::hasMember(Player* player) {
	for (int i = 0; i < groupMembers->size(); i++) {
		SceneObject* play = groupMembers->get(i);

		if (play == player)
			return true;
	}
	return false;
}

void GroupObjectImplementation::disband() {
	// this locked
	for (int i = 0; i < groupMembers->size(); ++i) {
		SceneObject* play = groupMembers->get(i);

		try {
			play->wlock((GroupObject*) _this);

			if (play->isPlayerCreature()) {
				PlayerCreature* playerCreature = (PlayerCreature*) play;
				playerCreature->removeChatRoom(groupChannel);

				playerCreature->setGroup(NULL);
				playerCreature->updateGroupId(0);
			}

			removeSquadLeaderBonuses(play);

			BaseMessage* msg = new SceneObjectDestroyMessage((GroupObject*) _this);
			play->sendMessage(msg);

			play->unlock();

		} catch (...) {
			System::out << "Exception in GroupObject::disband(Player* player)\n";
			play->unlock();
		}
	}


	if (groupChannel != NULL) {
		ChatRoom* room = groupChannel->getParent();
		ChatRoom* parent = room->getParent();

		ChatManager* chatManager = getZone()->getChatManager();

		chatManager->destroyRoom(groupChannel);
		chatManager->destroyRoom(room);

		groupChannel = NULL;
	}

	groupMembers->removeAll();
}

void GroupObjectImplementation::broadcastMessage(BaseMessage* msg) {
	for (int i = 0; i < groupMembers->size(); i++) {
		Player* play = groupMembers->get(i);

		play->sendMessage(msg->clone());
	}

	msg->finalize();
}

void GroupObjectImplementation::sendSystemMessage(SceneObject* player,
		const String& message, bool sendToSelf) {
	for (int i = 0; i < groupMembers->size(); i++) {
		SceneObject* play = groupMembers->get(i);

		if (play->isPlayerCreature()) {
			SceneObject* playerCreature = (PlayerCreature*) play;

			if (playerCreature != player) {
				playerCreature->sendSystemMessage(message);
			} else {
				if (sendToSelf)
					playerCreature->sendSystemMessage(message);
			}
		}
	}
}

void GroupObjectImplementation::sendSystemMessage(SceneObject* player,
		const String& file, const String& str, uint64 targetid, bool sendToSelf) {
	for (int i = 0; i < groupMembers->size(); i++) {
		SceneObject* play = groupMembers->get(i);

		if (play->isPlayerCreature()) {
			SceneObject* playerCreature = (PlayerCreature*) play;

			if (playerCreature != player) {
				playerCreature->sendSystemMessage(file, str, targetid);
			} else {
				if (sendToSelf)
					playerCreature->sendSystemMessage(file, str, targetid);
			}
		}
	}
}

void GroupObjectImplementation::sendSystemMessage(SceneObject* player,
		const String& file, const String& str, StfParameter* param,
		bool sendToSelf) {
	for (int i = 0; i < groupMembers.size(); i++) {
		SceneObject* play = groupMembers.get(i);

		if (play->isPlayerCreature()) {
			SceneObject* playerCreature = (PlayerCreature*) play;

			if (playerCreature != player) {
				playerCreature->sendSystemMessage(file, str, param);
			} else {
				if (sendToSelf)
					playerCreature->sendSystemMessage(file, str, param);
			}
		}
	}
}

void GroupObjectImplementation::makeLeader(SceneObject* player) {
	if (groupMembers->size() < 2)
		return;

	for (int i = 0; i < groupMembers->size(); ++i) {
		removeSquadLeaderBonuses(groupMembers->get(i));
	}

	SceneObject* temp = leader;
	leader = player;
	int i = 0;
	for (; i < groupMembers->size(); i++) {
		addSquadLeaderBonuses(groupMembers->get(i));

		if (groupMembers->get(i) == player) {
			groupMembers->set(0, player);
			groupMembers->set(i, temp);
			break;
		}
	}

	GroupObjectDeltaMessage6* grp = new GroupObjectDeltaMessage6((GroupObject*) _this);
	grp->updateLeader(player, temp, i);
	grp->close();

	broadcastMessage(grp);
}

float GroupObjectImplementation::getRangerBonusForHarvesting(SceneObject* player) {
	Player* temp;
	String skillBox = "outdoors_ranger_novice";
	String skillBox2 = "outdoors_ranger_master";

	float bonus = .2f;
	bool closeEnough = false;

	int i = 0;
	for (; i < groupMembers.size(); i++) {

		temp = groupMembers.get(i);

		try {
			if (temp != player)
				temp->wlock(player);

			if (temp->getFirstName() != player->getFirstName() && temp->isInRange(player, 64.0f) &&
					player->getZoneID() == temp->getZoneID())
				closeEnough = true;

			if (temp->hasSkillBox(skillBox))
				bonus = .3f;

			if (temp->hasSkillBox(skillBox2))
				bonus = .4f;

			if (temp != player)
				temp->unlock();
		} catch (...) {
			temp->error("unreported exception caught in GroupObjectImplementation::getRangerBonusForHarvesting");

			if (temp != player)
				temp->unlock();
		}

	}

	if (closeEnough)
		return bonus;
	else
		return 0.0f;
}

void GroupObjectImplementation::addSquadLeaderBonuses(CreatureObject* groupMember) {
	int meleeDefenseBonus = leader->getSkillMod("group_melee_defense");
	int rangedDefenseBonus = leader->getSkillMod("group_ranged_defense");
	int burstRunBonus = leader->getSkillMod("group_burst_run");
	int terrainNegotiationBonus = leader->getSkillMod("group_slope_move");

	groupMember->addSkillModBonus("melee_defense", meleeDefenseBonus, false);
	groupMember->addSkillModBonus("ranged_defense", rangedDefenseBonus, false);
	groupMember->addSkillModBonus("burst_run", burstRunBonus, false);
	groupMember->addSkillModBonus("slope_move", terrainNegotiationBonus, false);
}

void GroupObjectImplementation::removeSquadLeaderBonuses(CreatureObject* groupMember) {
	int meleeDefenseBonus = leader->getSkillMod("group_melee_defense");
	int rangedDefenseBonus = leader->getSkillMod("group_ranged_defense");
	int burstRunBonus = leader->getSkillMod("group_burst_run");
	int terrainNegotiationBonus = leader->getSkillMod("group_slope_move");

	groupMember->addSkillModBonus("melee_defense", -meleeDefenseBonus, false);
	groupMember->addSkillModBonus("ranged_defense", -rangedDefenseBonus, false);
	groupMember->addSkillModBonus("burst_run", -burstRunBonus, false);
	groupMember->addSkillModBonus("slope_move", -terrainNegotiationBonus, false);
}
