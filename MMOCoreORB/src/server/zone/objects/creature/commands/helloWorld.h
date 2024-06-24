#ifndef HELLOWORLDCOMMAND_H_
#define HELLOWORLDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class HelloWorldCommand : public QueueCommand {
public:

	HelloWorldCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!creature->isPlayerCreature()) // If not player, bail
			return GENERALERROR;

		creature->sendSystemMessage("Hello World!");

		return SUCCESS;
	}

};

#endif //HELLOWORLDCOMMAND_H_