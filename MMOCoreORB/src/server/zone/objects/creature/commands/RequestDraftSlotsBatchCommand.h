/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTDRAFTSLOTSBATCHCOMMAND_H_
#define REQUESTDRAFTSLOTSBATCHCOMMAND_H_

#include "server/zone/managers/crafting/CraftingManager.h"

class RequestDraftSlotsBatchCommand : public QueueCommand {
public:

	RequestDraftSlotsBatchCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		/**
		 * Argument 1 is the SchematicID
		 * Argument 2 is the SchematicCRC
		 */

		ManagedReference<CraftingManager* > craftingManager = creature->getZoneServer()->getCraftingManager();

		if(craftingManager == NULL || !creature->isPlayerCreature())
			return GENERALERROR;

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");
		String value;
		uint32 schematicID;

		while(tokenizer.hasMoreTokens()) {
			tokenizer.getStringToken(value);

			if(!tokenizer.hasMoreTokens())
				break;

			tokenizer.shiftTokens(1);

			try {
				schematicID = Integer::valueOf(value);

				craftingManager->sendDraftSlotsTo(creature, schematicID);
			} catch(Exception& e) {

				warning("Invalid draft slot request: " + value);
			}
		}

		return SUCCESS;
	}

};

#endif //REQUESTDRAFTSLOTSBATCHCOMMAND_H_
