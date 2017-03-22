/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef RESOURCECONTAINERTRANSFERCOMMAND_H_
#define RESOURCECONTAINERTRANSFERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/resource/ResourceContainer.h"

class ResourceContainerTransferCommand : public QueueCommand {
public:

	ResourceContainerTransferCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer tokenizer(arguments.toString());
		uint64 toContainerID = tokenizer.getLongToken();

		ManagedReference<ResourceContainer* > fromContainer = server->getZoneServer()->getObject(target).castTo<ResourceContainer*>();
		ManagedReference<ResourceContainer* > toContainer = server->getZoneServer()->getObject(toContainerID).castTo<ResourceContainer*>();

		if((fromContainer == NULL || toContainer == NULL || !fromContainer->isResourceContainer()
				|| !toContainer->isResourceContainer() || !creature->isPlayerCreature() || !fromContainer->isASubChildOf(creature) || !toContainer->isASubChildOf(creature)))
			return INVALIDTARGET;

		ManagedReference<SceneObject*> par = toContainer->getParent().get();

		if (par != NULL && par->isContainerFull()) {
			creature->sendSystemMessage("@container_error_message:container03");
			return GENERALERROR;
		}

		toContainer->combine(fromContainer);

		return SUCCESS;
	}

};

#endif //RESOURCECONTAINERTRANSFERCOMMAND_H_
