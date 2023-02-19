/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLACESTRUCTUREMODECOMMAND_H_
#define PLACESTRUCTUREMODECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/player/EnterStructurePlacementModeMessage.h"
#include "templates/manager/TemplateManager.h"
#include "templates/faction/Factions.h"

class PlaceStructureModeCommand : public QueueCommand {
public:

	PlaceStructureModeCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		if (creature->isRidingMount()) {
			creature->sendSystemMessage("@player_structure:cant_place_mounted");
			return INVALIDLOCOMOTION;
		}

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (creature->getParent() != nullptr) {
			creature->sendSystemMessage("@player_structure:not_inside"); //You can not place a structure while you are inside a building.
			return GENERALERROR;
		}

		ManagedReference<CityRegion*> city = creature->getCityRegion().get();

		if (city != nullptr && city->isClientRegion()) {
			creature->sendSystemMessage("@player_structure:not_permitted"); //Building is not permitted here.
			return INVALIDPARAMETERS;
		}

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);

		if (obj == nullptr || !obj->isDeedObject()) {
			creature->sendSystemMessage("@player_structure:not_a_deed"); //That is not a deed.
			return INVALIDTARGET;
		}

		if (!obj->isASubChildOf(creature))
			return GENERALERROR; //Deed must be in inventory...

		Deed* deed = cast<Deed*>(obj.get());

		//Check deed faction, player faction and status to make sure they are allowed to place a faction deeds (bases)
		if (deed->getFaction() != Factions::FACTIONNEUTRAL){
			if (creature->getFaction() == Factions::FACTIONNEUTRAL || creature->getFactionStatus() == FactionStatus::ONLEAVE){
				StringIdChatParameter message("@faction_perk:prose_not_neutral"); // You cannot use %TT if you are neutral or on leave.
				message.setTT(deed->getDisplayedName());

				creature->sendSystemMessage(message);
				return GENERALERROR;
			}

			if (deed->getFaction() != creature->getFaction()) {
				UnicodeString deedFaction = "";

				if (deed->isRebel()) {
					deedFaction = "Rebel";
				} else if (deed->isImperial()) {
					deedFaction = "Imperial";
				}

				StringIdChatParameter message("@faction_perk:prose_wrong_faction"); // You must be declared to %TO faction to use %TT.
				message.setTT(deed->getDisplayedName());
				message.setTO(deedFaction);

				creature->sendSystemMessage(message);
				return GENERALERROR;
			}
		}

		TemplateManager* templateManager = TemplateManager::instance();

		String serverTemplatePath = deed->getGeneratedObjectTemplate();
		Reference<SharedStructureObjectTemplate*> serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(serverTemplatePath.hashCode()));

		if (serverTemplate == nullptr)
			return GENERALERROR; //Template is unknown.

		int lots = serverTemplate->getLotSize();

		if (!ghost->hasLotsRemaining(lots)) {
			StringIdChatParameter param("@player_structure:not_enough_lots");
			param.setDI(lots);
			creature->sendSystemMessage(param);
			return GENERALERROR;
		}

		String clientTemplatePath = templateManager->getTemplateFile(serverTemplate->getClientObjectCRC());

		EnterStructurePlacementModeMessage* espmm = new EnterStructurePlacementModeMessage(deed->getObjectID(), clientTemplatePath);
		creature->sendMessage(espmm);

		return SUCCESS;
	}
};

#endif //PLACESTRUCTUREMODECOMMAND_H_
