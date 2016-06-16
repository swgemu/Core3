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

		if (playerObject)
		{
			if (playerObject->hasGodMode())
				godMode = true;
		}

		GroupManager* groupManager = GroupManager::instance();

		ManagedReference<SceneObject*> object = NULL;
		if (target != 0 && target != creature->getObjectID())
			object = server->getZoneServer()->getObject(target);
		else if (!arguments.isEmpty()) {
			StringTokenizer tokenizer(arguments.toString());
			if (tokenizer.hasMoreTokens()) {
				String name;
				tokenizer.getStringToken(name);
				name = name.toLowerCase();
				if (name != "self" && name != "this") {
					try {
						object = server->getPlayerManager()->getPlayer(name);
					} catch (ArrayIndexOutOfBoundsException& ex) {
						// this happens if the player wasn't found
					}
				}
			}
		}


		if (object == NULL)
			return GENERALERROR;


		if (object->isPlayerCreature()) {
			CreatureObject* player = cast<CreatureObject*>( object.get());
      		        creature->playEffect("clienteffect/player_clone_compile.cef", "");

			if (!player->getPlayerObject()->isIgnoring(creature->getFirstName().toLowerCase()) || godMode)
				groupManager->inviteToGroup(creature, player);
		}

		return SUCCESS;
	}

};

#endif //INVITECOMMAND_H_
