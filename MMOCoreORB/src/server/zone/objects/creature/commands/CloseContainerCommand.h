/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CLOSECONTAINERCOMMAND_H_
#define CLOSECONTAINERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"

class CloseContainerCommand : public QueueCommand {
public:
	CloseContainerCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
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

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject*> container = nullptr;

		StringTokenizer args(arguments.toString());

		if (args.hasMoreTokens()) {
			uint64 oid = args.getLongToken();

			container = zoneServer->getObject(oid);
		} else {
			container = zoneServer->getObject(target);
		}

		if (container == nullptr)
			return GENERALERROR;

		Locker clocker(container, creature);

		container->closeContainerTo(creature, false);
		container->notifyCloseContainer(creature);

		return SUCCESS;
	}
};

#endif // CLOSECONTAINERCOMMAND_H_
