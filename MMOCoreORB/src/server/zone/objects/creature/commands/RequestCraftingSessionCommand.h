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
		if(zoneServer == nullptr)
			return GENERALERROR;

		ManagedReference<SceneObject* > object = zoneServer->getObject(target);

		if(object == nullptr || !creature->isPlayerCreature())
			return INVALIDTARGET;

		ManagedReference<TradeSession*> tradeContainer = creature->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

		if (tradeContainer != nullptr) {
			server->getZoneServer()->getPlayerManager()->handleAbortTradeMessage(creature);
		}

		ManagedReference<CraftingTool*> craftingTool = nullptr;
		ManagedReference<CraftingStation*> craftingStation = nullptr;

		/// Logic for if target oid is crafting tool
		if(object->isCraftingTool()) {
			craftingTool = cast<CraftingTool*>( object.get());
		}

		if(object->isCraftingStation()) {
			craftingStation = cast<CraftingStation*>( object.get());
		}

		if (!checkStateMask(creature)) {
			if(craftingTool != nullptr && creature->isPlayerCreature()) {

				String message = "@ui_craft:err_start";
				craftingTool->sendToolStartFailure(creature, message);

			}
			return INVALIDSTATE;
		}

		if (!checkInvalidLocomotions(creature)) {
			if(craftingTool != nullptr && creature->isPlayerCreature()) {

				String message = "@ui_craft:err_start";
				craftingTool->sendToolStartFailure(creature, message);

			}
			return INVALIDLOCOMOTION;
		}

		/// If they are both null, we can't craft
		if(craftingTool == nullptr && craftingStation == nullptr) {
			creature->sendSystemMessage("Error starting crafting session, no tool or station found.  Please report this error");
			return GENERALERROR;
		}

		/**
		 * This command seems to have no arguments
		 * The target is either the crafting tool,
		 * or station clicked on
		 */

		/// Check if tool is in initiating creatures inventory
		if(craftingTool != nullptr && !craftingTool->isASubChildOf(creature)) {
			return GENERALERROR;
		}

		// Make sure station is in a building or outdoors and within range
		if(craftingStation != nullptr) {
			ManagedReference<SceneObject*> parent = craftingStation->getParent().get();

			if ((parent != nullptr && !parent->isCellObject()) || !creature->isInRange(craftingStation, 7.0)) {
				return GENERALERROR;
			}
		}

		/// Its a station, find the tool
		if(craftingStation != nullptr) {
			craftingTool = cast<CraftingTool*>(craftingStation->findCraftingTool(creature));
		}

		/// If tool isn't null we have a valid tool and can start the session
		if(craftingTool != nullptr) {

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

			if(craftingStation == nullptr) {
				ManagedReference<PlayerManager*> playerMan = zoneServer->getPlayerManager();

				if(playerMan == nullptr)
					return GENERALERROR;

				craftingStation = playerMan->getNearbyCraftingStation(creature, craftingTool->getToolType());
			}

			Reference<CraftingSession*> session = creature->getActiveSession(SessionFacadeType::CRAFTING).castTo<CraftingSession*>();
			if(session != nullptr) {
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
