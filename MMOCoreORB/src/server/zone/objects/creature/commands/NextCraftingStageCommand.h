/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef NEXTCRAFTINGSTAGECOMMAND_H_
#define NEXTCRAFTINGSTAGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sessions/TradeSession.h"

class NextCraftingStageCommand : public QueueCommand {
public:

	NextCraftingStageCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;


		/**
		 * Argument = 1 integer
		 * This argument is the stage for nextCraftingStage
		 */

		if(!creature->isPlayerCreature())
			return INVALIDTARGET;

		ManagedReference<TradeSession*> tradeContainer = creature->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		if (tradeContainer != NULL) {
			server->getZoneServer()->getPlayerManager()->handleAbortTradeMessage(creature);
		}

		Reference<CraftingSession*> session = creature->getActiveSession(SessionFacadeType::CRAFTING).castTo<CraftingSession*>();

		if(session == NULL) {
			return GENERALERROR;
		}

		StringTokenizer tokenizer(arguments.toString());

		int clientCounter = 0;

		if(tokenizer.hasMoreTokens()) {

			clientCounter = tokenizer.getIntToken();
		}

		Locker locker(session);
		session->nextCraftingStage(clientCounter);

		return SUCCESS;
	}

};

#endif //NEXTCRAFTINGSTAGECOMMAND_H_
