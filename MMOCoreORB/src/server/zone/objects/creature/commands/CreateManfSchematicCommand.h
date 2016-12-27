/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CREATEMANFSCHEMATICCOMMAND_H_
#define CREATEMANFSCHEMATICCOMMAND_H_

#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sessions/TradeSession.h"

class CreateManfSchematicCommand : public QueueCommand {
public:

	CreateManfSchematicCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		/**
		 * Arguments
		 *
		 * 1 Unicode String
		 * Contains clientCounter and int for practice
		 *
		 */

		if (!creature->isPlayerCreature())
			return INVALIDTARGET;

		ManagedReference<TradeSession*> tradeContainer = creature->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		if (tradeContainer != NULL) {
			server->getZoneServer()->getPlayerManager()->handleAbortTradeMessage(creature);
		}

		StringTokenizer tokenizer(arguments.toString());
		int clientCounter = 0;

		if(tokenizer.hasMoreTokens())
			clientCounter = tokenizer.getIntToken();
		else
			return GENERALERROR;

		Reference<CraftingSession*> session = creature->getActiveSession(SessionFacadeType::CRAFTING).castTo<CraftingSession*>();

		if(session == NULL) {
			warning("Trying to create manf schematic when no session exists");
			return GENERALERROR;
		}

		Locker locker(session);
		session->createManufactureSchematic(clientCounter);

		return SUCCESS;
	}

};

#endif //CREATEMANFSCHEMATICCOMMAND_H_
