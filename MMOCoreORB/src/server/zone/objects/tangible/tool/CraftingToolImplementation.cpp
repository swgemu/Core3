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

#include "CraftingTool.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/templates/tangible/tool/CraftingToolTemplate.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/objects/manufactureschematic/ingredientslots/IngredientSlot.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/objects/tangible/component/Component.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/player/PlayerObjectDeltaMessage9.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"

void CraftingToolImplementation::loadTemplateData(
		SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	CraftingToolTemplate* craftingToolData =
			dynamic_cast<CraftingToolTemplate*> (templateData);

	if (craftingToolData == NULL) {
		throw Exception("invalid template for CraftingTool");
	}

	type = craftingToolData->getToolType();

	complexityLevel = craftingToolData->getComplexityLevel();

	for (int i = 0; i < craftingToolData->getTabs().size(); ++i)
		enabledTabs.add(craftingToolData->getTabs().get(i));

	effectiveness = -14;
}

void CraftingToolImplementation::fillObjectMenuResponse(
		ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	if (getContainerObjectsSize() > 0 && status
			== "@crafting:tool_status_finished") {
		menuResponse->addRadialMenuItem(132, 3,
				"@ui_radial:craft_hopper_output");
	}

}

TangibleObject* CraftingToolImplementation::getPrototype() {
	if (getContainerObjectsSize() > 0)
		return cast<TangibleObject*> (getContainerObject(0));
	else
		return NULL;
}

int CraftingToolImplementation::handleObjectMenuSelect(
		CreatureObject* playerCreature, byte selectedID) {

	if(isASubChildOf(playerCreature)) {

		PlayerObject* playerObject = playerCreature->getPlayerObject();

		if (selectedID == 20) { // use object

		}

		if (selectedID == 132) { // use object

			if(!isFinished())
				return 0;

			ManagedReference<TangibleObject *> prototype = getPrototype();
			ManagedReference<SceneObject*> inventory =
					playerCreature->getSlottedObject("inventory");

			if (prototype == NULL) {

				while (getContainerObjectsSize() > 0) {
					//removeObject(getContainerObject(0));
					getContainerObject(0)->destroyObjectFromWorld(true);
				}

				playerCreature->sendSystemMessage(
						"Tool does not have a valid prototype, resetting tool.  Contact Kyle if you see this message");
				status = "@crafting:tool_status_ready";
				return 1;
			}

			if (inventory != NULL && inventory->getContainerObjectsSize() < 80) {

				playerCreature->sendSystemMessage("@system_msg:prototype_transferred");
				//removeObject(prototype);

				inventory->transferObject(prototype, -1, true);

				status = "@crafting:tool_status_ready";
			} else {
				playerCreature->sendSystemMessage("@system_msg:prototype_not_transferred");
			}

		}
	}

	return TangibleObjectImplementation::handleObjectMenuSelect(playerCreature, selectedID);
}

void CraftingToolImplementation::fillAttributeList(AttributeListMessage* alm,
		CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("craft_tool_effectiveness", Math::getPrecision(
			effectiveness, 2));

	alm->insertAttribute("craft_tool_status", status);

	if (craftersName != "") {

		alm->insertAttribute("crafter", craftersName);
	}
	if (objectSerial != "") {

		alm->insertAttribute("serial_number", objectSerial);
	}

	disperseItems();
}

void CraftingToolImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	/// useModifer is the effectiveness

	effectiveness = values->getCurrentValue("usemodifier");

	//craftingValues->toString();
}

Vector<uint32>* CraftingToolImplementation::getToolTabs() {
	return &enabledTabs;
}

void CraftingToolImplementation::sendToolStartFailure(CreatureObject* player, const String& message) {

	// Start Object Controller **(Failed to start crafting Session************
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			player->getObjectID(), 0x1B, 0x010C);
	objMsg->insertInt(0x10F);
	objMsg->insertInt(0);
	objMsg->insertByte(0);

	player->sendMessage(objMsg);

	player->sendSystemMessage(message);
}

void CraftingToolImplementation::disperseItems() {

	if(!isReady())
		return;

	ManagedReference<SceneObject*> craftedComponents = getSlottedObject("crafted_components");

	if(craftedComponents == NULL) {

		if(getContainerObjectsSize() == 0)
			return;

		ManagedReference<SceneObject*> prototype = getContainerObject(0);
		craftedComponents = prototype->getSlottedObject("crafted_components");

		if(craftedComponents == NULL) {
			prototype->destroyObjectFromWorld(true);
			return;
		}
	}

	if(craftedComponents->getContainerObjectsSize() > 0) {
		ManagedReference<SceneObject*> satchel = craftedComponents->getContainerObject(0);
		ManagedReference<SceneObject*> inventory = getParent();

		if(satchel != NULL && inventory != NULL) {
			while(satchel->getContainerObjectsSize() > 0) {
				ManagedReference<SceneObject*> object = satchel->getContainerObject(0);
				inventory->transferObject(object, -1, false);
				inventory->broadcastObject(object, true);
			}
		}
	}

	if(craftedComponents != NULL)
		craftedComponents->destroyObjectFromWorld(true);
}
