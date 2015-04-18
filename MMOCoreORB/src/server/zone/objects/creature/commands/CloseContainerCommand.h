/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLOSECONTAINERCOMMAND_H_
#define CLOSECONTAINERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/minigames/FishingManager.h"

class CloseContainerCommand : public QueueCommand {
public:

	CloseContainerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		/*StringBuffer msg; //target is the container
		msg << "target of container: 0x" << hex << target;
		creature->info(msg.toString(), true);*/

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<SceneObject*> container = NULL;

		StringTokenizer args(arguments.toString());

		if(args.hasMoreTokens()) {

			uint64 oid = args.getLongToken();
			container = server->getZoneServer()->getObject(oid);

		} else {
			container = server->getZoneServer()->getObject(target);
		}
		if (container == NULL)
			return GENERALERROR;

		Locker clocker(container, creature);

		container->closeContainerTo(cast<CreatureObject*>(creature), false);
		container->notifyCloseContainer(cast<CreatureObject*>(creature));

		return SUCCESS;
	}

};

#endif //CLOSECONTAINERCOMMAND_H_
