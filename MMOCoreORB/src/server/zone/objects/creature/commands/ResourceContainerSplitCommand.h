/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RESOURCECONTAINERSPLITCOMMAND_H_
#define RESOURCECONTAINERSPLITCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/resource/ResourceContainer.h"

class ResourceContainerSplitCommand : public QueueCommand {
public:

	ResourceContainerSplitCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer tokenizer(arguments.toString());
		int newStackSize = tokenizer.getIntToken();

		if (newStackSize < 1)
			return GENERALERROR;

		ManagedReference<ResourceContainer* > resourceContainer = server->getZoneServer()->getObject(target).castTo<ResourceContainer*>();

		if ((resourceContainer == NULL || !resourceContainer->isResourceContainer() ||!creature->isPlayerCreature()))
			return INVALIDTARGET;

		if(!resourceContainer->isASubChildOf(creature)) {
			creature->sendSystemMessage("@container_error_message:container08");
			return INVALIDTARGET;
		}

		ManagedReference<SceneObject*> objectsParent = resourceContainer->getParent();

		if (objectsParent == NULL ||
				objectsParent->isCellObject()) {

			creature->sendSystemMessage("@container_error_message:container03");
			return GENERALERROR;
		}

		resourceContainer->split(newStackSize);

		return SUCCESS;
	}

};

#endif //RESOURCECONTAINERSPLITCOMMAND_H_
