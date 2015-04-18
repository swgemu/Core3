/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTRESOURCEWEIGHTSBATCHCOMMAND_H_
#define REQUESTRESOURCEWEIGHTSBATCHCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/crafting/CraftingManager.h"

class RequestResourceWeightsBatchCommand : public QueueCommand {
public:

	RequestResourceWeightsBatchCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<CraftingManager* > craftingManager = creature->getZoneServer()->getCraftingManager();

		if(craftingManager == NULL || !creature->isPlayerCreature())
			return GENERALERROR;

		StringTokenizer tokenizer(arguments.toString());

		String value;
		uint32 schematicID;

		while(tokenizer.hasMoreTokens()) {
			tokenizer.getStringToken(value);

			try {
				schematicID = Integer::valueOf(value);

				craftingManager->sendResourceWeightsTo(creature, schematicID);
			} catch(Exception& e) {
				warning("Invalid draft slot request: " + value);
			}
		}

		return SUCCESS;
	}

};

#endif //REQUESTRESOURCEWEIGHTSBATCHCOMMAND_H_
