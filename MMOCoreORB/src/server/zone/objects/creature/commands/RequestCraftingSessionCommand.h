/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTCRAFTINGSESSIONCOMMAND_H_
#define REQUESTCRAFTINGSESSIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"
#include "server/zone/objects/tangible/tool/CraftingStation.h"
#include "server/zone/objects/player/sessions/crafting/CraftingSession.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/player/sessions/TradeSession.h"

class RequestCraftingSessionCommand : public QueueCommand {
public:

	RequestCraftingSessionCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		ManagedReference<ZoneServer*> zoneServer = creature->getZoneServer();
		if(zoneServer == NULL)
			return GENERALERROR;

		ManagedReference<SceneObject* > object = zoneServer->getObject(target);

		if(object == NULL || !creature->isPlayerCreature())
			return INVALIDTARGET;

		ManagedReference<TradeSession*> tradeContainer = creature->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		if (tradeContainer != NULL) {
			server->getZoneServer()->getPlayerManager()->handleAbortTradeMessage(creature);
		}

		ManagedReference<CraftingTool*> craftingTool = NULL;
		ManagedReference<CraftingStation*> craftingStation = NULL;

		/// Logic for if target oid is crafting tool
		if(object->isCraftingTool()) {
			craftingTool = cast<CraftingTool*>( object.get());
		}

		if(object->isCraftingStation()) {
			craftingStation = cast<CraftingStation*>( object.get());
		}

		if (!checkStateMask(creature)) {
			if(craftingTool != NULL && creature->isPlayerCreature()) {

				String message = "@ui_craft:err_start";
				craftingTool->sendToolStartFailure(creature, message);

			}
			return INVALIDSTATE;
		}

		if (!checkInvalidLocomotions(creature)) {
			if(craftingTool != NULL && creature->isPlayerCreature()) {

				String message = "@ui_craft:err_start";
				craftingTool->sendToolStartFailure(creature, message);

			}
			return INVALIDLOCOMOTION;
		}

		/// If they are both null, we can't craft
		if(craftingTool == NULL && craftingStation == NULL) {
			creature->sendSystemMessage("Error starting crafting session, no tool or station found.  Please report this error");
			return GENERALERROR;
		}

		/**
		 * This command seems to have no arguments
		 * The target is either the crafting tool,
		 * or station clicked on
		 */

		/// Check if tool is in initiating creatures inventory
		if(craftingTool != NULL && !craftingTool->isASubChildOf(creature)) {
			return GENERALERROR;
		}

		// Make sure station is in a building or outdoors and within range
		if(craftingStation != NULL) {
			ManagedReference<SceneObject*> parent = craftingStation->getParent().get();

			if ((parent != NULL && !parent->isCellObject()) || !creature->isInRange(craftingStation, 7.0)) {
				return GENERALERROR;
			}
		}

		/// Its a station, find the tool
		if(craftingStation != NULL) {
			craftingTool = cast<CraftingTool*>(craftingStation->findCraftingTool(creature));
		}

		/// If tool isn't null we have a valid tool and can start the session
		if(craftingTool != NULL) {

			if (craftingTool->isFinished()) {
				String message = "@system_msg:crafting_tool_full";
				craftingTool->sendToolStartFailure(creature, message);
				return GENERALERROR;
			}

			if (craftingTool->isBusy()) {
				String message = "@system_msg:crafting_tool_creating_prototype";
				craftingTool->sendToolStartFailure(creature, message);
				return GENERALERROR;
			}

			if(craftingStation == NULL) {
				ManagedReference<PlayerManager*> playerMan = zoneServer->getPlayerManager();

				if(playerMan == NULL)
					return GENERALERROR;

				craftingStation = playerMan->getNearbyCraftingStation(creature, craftingTool->getToolType());
			}

			Reference<CraftingSession*> session = creature->getActiveSession(SessionFacadeType::CRAFTING).castTo<CraftingSession*>();
			if(session != NULL) {
				Locker locker(session);
				session->cancelSession();
			}

			ManagedReference<CraftingSession*> craftingSession = new CraftingSession(creature);

			Locker locker(craftingTool);

			if(!craftingSession->initializeSession(craftingTool, craftingStation)) {
				String message = "@ui_craft@err_no_crafting_tool";
				craftingTool->sendToolStartFailure(creature, message);
				return GENERALERROR;
			}

		} else {
			creature->sendSystemMessage("There are no tools available for this station");
			return INVALIDTARGET;
		}

		return SUCCESS;
	}
};

#endif //REQUESTCRAFTINGSESSIONCOMMAND_H_
