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

	MakeLeaderCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		GroupManager* groupManager = GroupManager::instance();

		if (groupManager == nullptr)
			return GENERALERROR;

		ZoneServer* zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		bool galaxyWide = ConfigManager::instance()->getBool("Core3.PlayerManager.GalaxyWideGrouping", false);

		ManagedReference<SceneObject*> object = nullptr;
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
			object = zoneServer->getObject(target);

			if (object == nullptr || !object->isCreatureObject())
				return GENERALERROR;

			tarCreo = object->asCreatureObject();
		}

		if (tarCreo == nullptr || !tarCreo->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<GroupObject*> group = creature->getGroup();

		if (group == nullptr)
			return GENERALERROR;

		groupManager->makeLeader(group, creature, tarCreo);

		return SUCCESS;
	}

};

#endif //MAKELEADERCOMMAND_H_

