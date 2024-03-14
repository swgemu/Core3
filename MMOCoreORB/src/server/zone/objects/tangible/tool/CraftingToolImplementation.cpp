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

	CraftingToolTemplate* craftingToolData = dynamic_cast<CraftingToolTemplate*>(templateData);

	if (craftingToolData == nullptr) {
		throw Exception("invalid template for CraftingTool");
	}

	type = craftingToolData->getToolType();

	complexityLevel = craftingToolData->getComplexityLevel();
	forceCriticalAssembly = craftingToolData->getForceCriticalAssembly();
	forceCriticalExperiment = craftingToolData->getForceCriticalExperiment();

	for (int i = 0; i < craftingToolData->getTabs().size(); ++i)
		enabledTabs.add(craftingToolData->getTabs().get(i));
}

void CraftingToolImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	if (getContainerObjectsSize() > 0) {
		status = TOOL_FINISHED; // "@crafting:tool_status_finished"
	} else {
		status = TOOL_READY; // "@crafting:tool_status_ready"
	}

	setCountdownTimer(0, false);
}

void CraftingToolImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	if (isFinished()) {
		menuResponse->addRadialMenuItem(RadialOptions::SERVER_ITEM_OPTIONS, 3, "@ui_radial:craft_hopper_output");
	}
}

Reference<TangibleObject*> CraftingToolImplementation::getPrototype() {
	if (getContainerObjectsSize() > 0)
		return getContainerObject(0).castTo<TangibleObject*>();
	else
		return nullptr;
}

int CraftingToolImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (!isASubChildOf(player))
		return 0;

	int toolSize = getContainerObjectsSize();

	// Get Finished Prototype
	if (selectedID == RadialOptions::SERVER_ITEM_OPTIONS) {
		// Tool is not finished
		if (!isFinished())
			return 0;

		ManagedReference<TangibleObject*> prototype = getPrototype();

		// Prototype is null, unable to stranfer
		if (prototype == nullptr) {
			status = TOOL_READY;

			return 1;
		}

		ManagedReference<SceneObject*> inventory = player->getInventory();

		if (inventory == nullptr)
			return 0;

		int totalLimit = inventory->getContainerVolumeLimit();
		int totalObjects = inventory->getCountableObjectsRecursive();

		// Check if the player has made space and attempt to transfer the prototype
		if (totalLimit > totalObjects && inventory->transferObject(prototype, -1, true, true)) {
			player->sendSystemMessage("@system_msg:prototype_transferred");

			status = TOOL_READY;
		} else {
			player->sendSystemMessage("@system_msg:prototype_not_transferred");
		}

		return 1;
	}

	return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

void CraftingToolImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
	TangibleObjectImplementation::fillAttributeList(alm, player);

	alm->insertAttribute("craft_tool_effectiveness", Math::getPrecision(effectiveness, 2));

	String statusString = "@crafting:tool_status_ready";

	if (status == TOOL_FINISHED) {
		statusString = "@crafting:tool_status_finished";
	} else if (status == TOOL_WORKING) {
		statusString = "@crafting:tool_status_working";
	}

	alm->insertAttribute("craft_tool_status", statusString);

	if (forceCriticalAssembly > 0)
		alm->insertAttribute("@crafting:crit_assembly", forceCriticalAssembly);

	if (forceCriticalExperiment > 0)
		alm->insertAttribute("@crafting:crit_experiment", forceCriticalExperiment);
}

void CraftingToolImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	// useModifer is the effectiveness
	effectiveness = values->getCurrentValue("usemodifier");
}

Vector<uint32>* CraftingToolImplementation::getToolTabs() {
	return &enabledTabs;
}

void CraftingToolImplementation::sendToolStartFailure(CreatureObject* player, const String& message) {
	// Start Object Controller **(Failed to start crafting Session************
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(player->getObjectID(), 0x1B, 0x010C);
	objMsg->insertInt(0x10F);
	objMsg->insertInt(0);
	objMsg->insertByte(0);

	player->sendMessage(objMsg);

	player->sendSystemMessage(message);
}

/*
void CraftingToolImplementation::disperseItems() {
	if (!isReady())
		return;

	Locker locker(_this.getReferenceUnsafeStaticCast());

	ManagedReference<SceneObject*> craftedComponents = getSlottedObject("crafted_components");
	ManagedReference<SceneObject*> prototype = nullptr;

	if (getContainerObjectsSize() > 0)
		prototype = getContainerObject(0);

	if (craftedComponents == nullptr) {
		if (prototype == nullptr)
			return;

		craftedComponents = prototype->getSlottedObject("crafted_components");
	}

	if (craftedComponents != nullptr && craftedComponents->getContainerObjectsSize() > 0) {
		ManagedReference<SceneObject*> satchel = craftedComponents->getContainerObject(0);
		ManagedReference<SceneObject*> inventory = getParent().get();

		if (satchel != nullptr && inventory != nullptr) {
			while (satchel->getContainerObjectsSize() > 0) {
				ManagedReference<SceneObject*> object = satchel->getContainerObject(0);

				inventory->transferObject(object, -1, false);
				inventory->broadcastObject(object, true);
			}
		}
	}

	if (craftedComponents != nullptr) {
		Locker clocker(craftedComponents, _this.getReferenceUnsafeStaticCast());
		craftedComponents->destroyObjectFromWorld(true);
	}

	if (prototype != nullptr) {
		Locker clocker(prototype, _this.getReferenceUnsafeStaticCast());
		prototype->destroyObjectFromWorld(true);
	}
}*/

Reference<ManufactureSchematic*> CraftingToolImplementation::getManufactureSchematic() {
	return getSlottedObject("test_manf_schematic").castTo<ManufactureSchematic*>();
}
