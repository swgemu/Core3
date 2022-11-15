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

		if((fromContainer == nullptr || toContainer == nullptr || !fromContainer->isResourceContainer()
				|| !toContainer->isResourceContainer() || !creature->isPlayerCreature() || !fromContainer->isASubChildOf(creature) || !toContainer->isASubChildOf(creature)))
			return INVALIDTARGET;

		ManagedReference<SceneObject*> parent = toContainer->getParent().get();

		if (parent == nullptr)
			return GENERALERROR;

		if (parent->getContainerObjectsSize() > parent->getContainerVolumeLimit()) {
			creature->sendSystemMessage("@error_message:inv_full"); //Your inventory is full.
			return GENERALERROR;
		}

		toContainer->combine(fromContainer);

		return SUCCESS;
	}

};

#endif //RESOURCECONTAINERTRANSFERCOMMAND_H_
