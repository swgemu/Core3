/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GMCREATESPECIFICRESOURCECOMMAND_H_
#define GMCREATESPECIFICRESOURCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/resource/ResourceManager.h"

class GmCreateSpecificResourceCommand : public QueueCommand {
public:

	GmCreateSpecificResourceCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		StringTokenizer tokenizer(arguments.toString());

		if(!tokenizer.hasMoreTokens() || !creature->isPlayerCreature())
			return INVALIDPARAMETERS;

		String restype;
		tokenizer.getStringToken(restype);

		ManagedReference<ResourceManager* > resourceManager = server->getZoneServer()->getResourceManager();
		resourceManager->createResourceSpawn(creature, restype);

		return SUCCESS;
	}

};

#endif //GMCREATESPECIFICRESOURCECOMMAND_H_
