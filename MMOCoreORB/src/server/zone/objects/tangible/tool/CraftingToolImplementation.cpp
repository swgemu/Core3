/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "engine/engine.h"

#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "templates/tangible/tool/CraftingToolTemplate.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/sessions/crafting/CraftingSession.h"

void CraftingToolImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	CraftingToolTemplate* craftingToolData = dynamic_cast<CraftingToolTemplate*> (templateData);

	if (craftingToolData == NULL) {
		throw Exception("invalid template for CraftingTool");
	}

	type = craftingToolData->getToolType();

	complexityLevel = craftingToolData->getComplexityLevel();
	forceCriticalAssembly = craftingToolData->getForceCriticalAssembly();
	forceCriticalExperiment = craftingToolData->getForceCriticalExperiment();

	for (int i = 0; i < craftingToolData->getTabs().size(); ++i)
		enabledTabs.add(craftingToolData->getTabs().get(i));
}

void CraftingToolImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	if (getContainerObjectsSize() > 0 && status	== "@crafting:tool_status_finished") {
		menuResponse->addRadialMenuItem(132, 3, "@ui_radial:craft_hopper_output");
	}

}

Reference<TangibleObject*> CraftingToolImplementation::getPrototype() {
	if (getContainerObjectsSize() > 0)
		return getContainerObject(0).castTo<TangibleObject*> ();
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
			ManagedReference<SceneObject*> inventory = playerCreature->getSlottedObject("inventory");

			if (prototype == NULL) {
				while (getContainerObjectsSize() > 0) {
					getContainerObject(0)->destroyObjectFromWorld(true);
				}

				playerCreature->sendSystemMessage("Tool does not have a valid prototype, resetting tool.  Contact Kyle if you see this message");
				status = "@crafting:tool_status_ready";
				return 1;
			}

			if (inventory != NULL && inventory->getContainerObjectsSize() < 80) {
				playerCreature->sendSystemMessage("@system_msg:prototype_transferred");
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

	alm->insertAttribute("craft_tool_effectiveness", Math::getPrecision(effectiveness, 2));
	alm->insertAttribute("craft_tool_status", status);

	if (forceCriticalAssembly > 0)
		alm->insertAttribute("@crafting:crit_assembly", forceCriticalAssembly);

	if (forceCriticalExperiment > 0)
		alm->insertAttribute("@crafting:crit_experiment", forceCriticalExperiment);

	Reference<CraftingSession*> session = object->getActiveSession(SessionFacadeType::CRAFTING).castTo<CraftingSession*>();
	if(session == NULL && getParent() != NULL) {
		disperseItems();
	}
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

	Locker locker(_this.getReferenceUnsafeStaticCast());

	ManagedReference<SceneObject*> craftedComponents = getSlottedObject("crafted_components");
	ManagedReference<SceneObject*> prototype = NULL;

	if(getContainerObjectsSize() > 0)
		 prototype = getContainerObject(0);

	if(craftedComponents == NULL) {

		if(prototype == NULL)
			return;

		craftedComponents = prototype->getSlottedObject("crafted_components");
	}

	if(craftedComponents != NULL  && craftedComponents->getContainerObjectsSize() > 0) {
		ManagedReference<SceneObject*> satchel = craftedComponents->getContainerObject(0);
		ManagedReference<SceneObject*> inventory = getParent().get();

		if(satchel != NULL && inventory != NULL) {
			while(satchel->getContainerObjectsSize() > 0) {
				ManagedReference<SceneObject*> object = satchel->getContainerObject(0);
				inventory->transferObject(object, -1, false);
				inventory->broadcastObject(object, true);
			}
		}
	}

	if(craftedComponents != NULL) {
		Locker clocker(craftedComponents, _this.getReferenceUnsafeStaticCast());
		craftedComponents->destroyObjectFromWorld(true);
	}

	if(prototype != NULL) {
		Locker clocker(prototype, _this.getReferenceUnsafeStaticCast());
		prototype->destroyObjectFromWorld(true);
	}
}

Reference<ManufactureSchematic*> CraftingToolImplementation::getManufactureSchematic() {
	return getSlottedObject("test_manf_schematic").castTo<ManufactureSchematic*>();
}
