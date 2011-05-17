/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef PLACESTRUCTUREMODECOMMAND_H_
#define PLACESTRUCTUREMODECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/deed/building/BuildingDeed.h"
#include "server/zone/packets/player/EnterStructurePlacementModeMessage.h"
#include "server/zone/templates/tangible/SharedBuildingObjectTemplate.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/planet/PlanetManager.h"

class PlaceStructureModeCommand : public QueueCommand {
public:

	PlaceStructureModeCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		PlayerCreature* player = (PlayerCreature*) creature;

		ZoneServer* zserv = server->getZoneServer();

		if (zserv == NULL)
			return GENERALERROR;

		ManagedReference<SceneObject*> obj = zserv->getObject(target);

		if (obj == NULL)
			return GENERALERROR;

		if (!obj->isBuildingDeed() && !obj->isInstallationDeed())
			return GENERALERROR;

		ManagedReference<Deed*> deed = (Deed*) obj.get();

		//Need to lock the deed ?
		Locker _locker(deed);

		if (creature->isRidingMount()) {
			creature->sendSystemMessage("player_structure", "cant_place_mounted"); //You may not place a structure while mounted or riding a vehicle.
			return GENERALERROR;
		}

		if (creature->getParentID() > 0) {
			creature->sendSystemMessage("player_structure", "not_inside"); //You can not place a structure while you are inside a building.
			return GENERALERROR;
		}

		TemplateManager* templateManager = TemplateManager::instance();

		String structureTemplateName = deed->getGeneratedObjectTemplate();
		uint32 structureTemplateCRC = structureTemplateName.hashCode();

		SharedStructureObjectTemplate* structureTemplate = dynamic_cast<SharedStructureObjectTemplate*>(templateManager->getTemplate(structureTemplateCRC));

		if (structureTemplate == NULL) {
			player->error("Invalid structure template used to enter placeStructureMode " + structureTemplateName);
			return GENERALERROR;
		}

		int lotsRemaining = player->getLotsRemaining();
		int lotsNeeded = structureTemplate->getLotSize();

		if (lotsRemaining < lotsNeeded) {
			StringIdChatParameter stringId;
			stringId.setStringId("@player_structure:not_enough_lots"); //This structure requires %DI lots.
			stringId.setDI(lotsNeeded);
			player->sendSystemMessage(stringId);
			return GENERALERROR;
		}

		ManagedReference<Zone*> zone = player->getZone();

		if (zone == NULL || !structureTemplate->isAllowedZone(zone->getZoneName())) {
			player->sendSystemMessage("@player_structure:wrong_planet"); //That deed cannot be used on this planet.
			return GENERALERROR;
		}

		String planetName = zone->getZoneName();

		/*if (planetName == "rori" || planetName == "yavin4") {
			player->sendSystemMessage("Structure placement is currently disabled on this planet");
			return GENERALERROR;
		}*/

		PlanetManager* planetManager = player->getZone()->getPlanetManager();
		StringId errorStf;

		if (planetManager->isNoBuildArea(player->getPositionX(), player->getPositionY(), errorStf)) {
			StringIdChatParameter sendString("player_structure", "city_too_close");
			sendString.setTO(errorStf.getFile(), errorStf.getStringID());

			player->sendSystemMessage(sendString);

			return GENERALERROR;
		}

		ManagedReference<CityRegion*> cityRegion = player->getCityRegion();

		Vector<ManagedReference<ActiveArea*> >* areas = player->getActiveAreas();

		if (cityRegion != NULL) {
			//Check if it's a player region, or a static region.

			player->sendSystemMessage("You cant place a structure here");
			return GENERALERROR;
		}

		int clientObjectCRC = structureTemplate->getClientObjectCRC();

		String clientTemplateString = structureTemplateName;

		if (clientObjectCRC != structureTemplateCRC)
			clientTemplateString = templateManager->getTemplateFile(clientObjectCRC);

		EnterStructurePlacementModeMessage* espm = new EnterStructurePlacementModeMessage(deed->getObjectID(), clientTemplateString);
		player->sendMessage(espm);

		return SUCCESS;
	}
};

#endif //PLACESTRUCTUREMODECOMMAND_H_
