/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SELECTDRAFTSCHEMATICCOMMAND_H_
#define SELECTDRAFTSCHEMATICCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sessions/TradeSession.h"

class SelectDraftSchematicCommand : public QueueCommand {
public:

	SelectDraftSchematicCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		/**
		 * Argument = 1 integer
		 * This argument is the index of the schematic in the players schematic list
		 */

	    if(!creature->isPlayerCreature())
			return INVALIDTARGET;

	    ManagedReference<TradeSession*> tradeContainer = creature->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

	    if (tradeContainer != NULL) {
	    	server->getZoneServer()->getPlayerManager()->handleAbortTradeMessage(creature);
	    }

	    ManagedReference<CreatureObject* > player = creature;

		Reference<CraftingSession*> session = creature->getActiveSession(SessionFacadeType::CRAFTING).castTo<CraftingSession*>();

		if(session == NULL) {
			return GENERALERROR;
		}

		StringTokenizer tokenizer(arguments.toString());

		int index = 0;

		if(tokenizer.hasMoreTokens()) {

			index = tokenizer.getIntToken();

		} else {
			player->sendSystemMessage("@ui_craft:err_no_draft_schematic_selected");
			return GENERALERROR;
		}

		Locker locker(session);
		session->selectDraftSchematic(index);

		return SUCCESS;
	}

};

#endif //SELECTDRAFTSCHEMATICCOMMAND_H_
