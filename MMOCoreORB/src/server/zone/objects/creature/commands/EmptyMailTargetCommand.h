/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef EMPTYMAILTARGETCOMMAND_H_
#define EMPTYMAILTARGETCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"

class EmptyMailTargetCommand : public QueueCommand {
public:

	EmptyMailTargetCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<CreatureObject* > targetCreature = server->getZoneServer()->getObject(target).castTo<CreatureObject*>();
		StringTokenizer args(arguments.toString());
		String firstName;

		if (args.hasMoreTokens()) {
			args.getStringToken(firstName);
			targetCreature = server->getZoneServer()->getPlayerManager()->getPlayer(firstName);
		}

		if (targetCreature == NULL || !targetCreature->isPlayerCreature())
			return INVALIDTARGET;

		PlayerObject* ghost = targetCreature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		Locker clocker(targetCreature, creature);

		ghost->deleteAllPersistentMessages();

		return SUCCESS;
	}

};

#endif //EMPTYMAILTARGETCOMMAND_H_
