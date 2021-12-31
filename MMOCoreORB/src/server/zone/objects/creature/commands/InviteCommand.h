/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef INVITECOMMAND_H_
#define INVITECOMMAND_H_


#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/ZoneServer.h"

class InviteCommand : public QueueCommand {
public:

	InviteCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		PlayerObject* playerObject = creature->getPlayerObject();
		bool godMode = false;

		if (playerObject) {
			if (playerObject->hasGodMode())
				godMode = true;
		}

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		bool galaxyWide = ConfigManager::instance()->getBool("Core3.PlayerManager.GalaxyWideGrouping", false);

		if (galaxyWide && (object == nullptr || !object->isPlayerCreature())) {
			StringTokenizer args(arguments.toString());
			String firstName;

			if (args.hasMoreTokens())
				args.getStringToken(firstName);

			ZoneServer* zoneServer = server->getZoneServer();

			if (zoneServer == nullptr)
				return GENERALERROR;

			PlayerManager* playerMan = zoneServer->getPlayerManager();

			if (playerMan == nullptr)
				return GENERALERROR;

			object = playerMan->getPlayer(firstName);
		}

		GroupManager* groupManager = GroupManager::instance();

		if (object == nullptr || groupManager == nullptr)
			return GENERALERROR;


		if (object->isPlayerCreature()) {
			CreatureObject* player = cast<CreatureObject*>( object.get());

		if (player != nullptr && (!player->getPlayerObject()->isIgnoring(creature->getFirstName()) || godMode))
			groupManager->inviteToGroup(creature, player);
		}

		return SUCCESS;
	}

};

#endif //INVITECOMMAND_H_

