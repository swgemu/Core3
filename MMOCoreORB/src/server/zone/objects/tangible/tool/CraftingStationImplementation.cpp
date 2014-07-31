/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
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

#include "engine/engine.h"

#include "server/zone/objects/tangible/tool/CraftingStation.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/templates/tangible/tool/CraftingStationTemplate.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"

void CraftingStationImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	CraftingStationTemplate* craftingStationData = dynamic_cast<CraftingStationTemplate*>(templateData);

	type = craftingStationData->getStationType();
	complexityLevel = craftingStationData->getComplexityLevel();
}

void CraftingStationImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	/*ManagedReference<BuildingObject*> building = cast<BuildingObject*>(getRootParent());

	if(building != NULL && !isASubChildOf(player)) {
		if(building->isOnAdminList(player) && getSlottedObject("ingredient_hopper") != NULL) {
			menuResponse->addRadialMenuItem(68, 3, "@ui_radial:craft_hopper_input"); //Open
		}
	}*/
}

int CraftingStationImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	/*if (selectedID == 68 && getSlottedObject("ingredient_hopper") != NULL) { // use object

		ManagedReference<BuildingObject*> building = cast<BuildingObject*>(getRootParent());

		if(building != NULL && !isASubChildOf(player)) {
			if(building->isOnAdminList(player))
				sendInputHopper(player);
		}
	}*/

	return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

void CraftingStationImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("stationmod", Math::getPrecision(effectiveness, 2));
}

void CraftingStationImplementation::sendInputHopper(CreatureObject* player) {

	/*ManagedReference<SceneObject*> inputHopper = getSlottedObject("ingredient_hopper");

	if(inputHopper == NULL) {
		return;
	}

	inputHopper->sendDestroyTo(player);
	inputHopper->closeContainerTo(player, true);

	inputHopper->sendWithoutContainerObjectsTo(player);
	inputHopper->openContainerTo(player);*/
}

SceneObject* CraftingStationImplementation::findCraftingTool(CreatureObject* player) {

	ManagedReference<SceneObject*> inventory = player->getSlottedObject(
			"inventory");
	Locker inventoryLocker(inventory);
	SceneObject* craftingTool = NULL;

	for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {

		SceneObject* object = inventory->getContainerObject(i);

		if (object != NULL && object->isCraftingTool()) {

			CraftingTool* tool = cast<CraftingTool*>( object);

			if(!tool->isReady())
				continue;

			int toolType = tool->getToolType();

			if (toolType == type) {
				return object;
			}

			if (toolType == CraftingTool::JEDI && type
					== CraftingTool::WEAPON) {
				craftingTool = object;
			}
		}

	}
	return craftingTool;
}

void CraftingStationImplementation::createChildObjects() {

}

void CraftingStationImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	/// useModifer is the effectiveness

	effectiveness = values->getCurrentValue("usemodifier");

	/*if(firstUpdate && values->hasSlotFilled("storage_compartment")) {
		String ingredientHopperName = "object/tangible/hopper/crafting_station_hopper/crafting_station_ingredient_hopper_structure_small.iff";
		ManagedReference<SceneObject*> ingredientHopper = server->getZoneServer()->createObject(ingredientHopperName.hashCode(), 1);

		transferObject(ingredientHopper, 4, true);
	}*/

	//craftingValues->toString();
}
