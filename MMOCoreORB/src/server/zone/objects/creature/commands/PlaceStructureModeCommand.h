/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef PLACESTRUCTUREMODECOMMAND_H_
#define PLACESTRUCTUREMODECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/player/EnterStructurePlacementModeMessage.h"
#include "templates/manager/TemplateManager.h"

class PlaceStructureModeCommand : public QueueCommand {
public:

	PlaceStructureModeCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		if (creature->isRidingMount()) {
			creature->sendSystemMessage("@player_structure:cant_place_mounted");
			return INVALIDLOCOMOTION;
		}

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;


		if (creature->getParent() != NULL) {
			creature->sendSystemMessage("@player_structure:not_inside"); //You can not place a structure while you are inside a building.
			return GENERALERROR;
		}

		ManagedReference<CityRegion*> city = creature->getCityRegion().get();

		if (city != NULL && city->isClientRegion()) {
			creature->sendSystemMessage("@player_structure:not_permitted"); //Building is not permitted here.
			return INVALIDPARAMETERS;
		}

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);

		if (obj == NULL || !obj->isDeedObject()) {
			creature->sendSystemMessage("@player_structure:not_a_deed"); //That is not a deed.
			return INVALIDTARGET;
		}

		if (!obj->isASubChildOf(creature))
			return GENERALERROR; //Deed must be in inventory...

		Deed* deed = cast<Deed*>(obj.get());

		TemplateManager* templateManager = TemplateManager::instance();

		String serverTemplatePath = deed->getGeneratedObjectTemplate();
		Reference<SharedStructureObjectTemplate*> serverTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(serverTemplatePath.hashCode()));

		if (serverTemplate == NULL)
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
