/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MAKELEADERCOMMAND_H_
#define MAKELEADERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/chat/ChatManager.h"


class MakeLeaderCommand : public QueueCommand {
public:
	MakeLeaderCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		bool galaxyWide = ConfigManager::instance()->getBool("Core3.PlayerManager.GalaxyWideGrouping", false);

		ManagedReference<CreatureObject*> tarCreo = nullptr;

		StringTokenizer args(arguments.toString());

		if (galaxyWide && args.hasMoreTokens()) {
			String firstName;

			args.getStringToken(firstName);

			if (firstName != "") {
				ChatManager* chatManager = zoneServer->getChatManager();

				if (chatManager == nullptr)
					return GENERALERROR;

				tarCreo = chatManager->getPlayer(firstName);
			}
		} else {
			ManagedReference<SceneObject*> object = zoneServer->getObject(target);

			if (object == nullptr || !object->isCreatureObject())
				return GENERALERROR;

			tarCreo = object->asCreatureObject();
		}

		if (tarCreo == nullptr || !tarCreo->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<GroupObject*> group = creature->getGroup();

		if (group == nullptr)
			return GENERALERROR;

		uint64 leaderID = group->getLeaderID();

		if (leaderID != creature->getObjectID()) {
			creature->sendSystemMessage("@group:must_be_leader");
			return GENERALERROR;
		} else if (leaderID == tarCreo->getObjectID()) {
			// target is already the leader
			return GENERALERROR;
		}

		Reference<CreatureObject*> leaderRef = creature;

		Core::getTaskManager()->executeTask([group, leaderRef, tarCreo]() {
			if (group == nullptr || leaderRef == nullptr || tarCreo == nullptr)
				return;

			GroupManager* groupManager = GroupManager::instance();

			if (groupManager == nullptr)
				return;

			Locker locker(group);

			groupManager->makeLeader(group, leaderRef, tarCreo);
		}, "MakeGroupLeaderLambda");

		return SUCCESS;
	}

};

#endif //MAKELEADERCOMMAND_H_

