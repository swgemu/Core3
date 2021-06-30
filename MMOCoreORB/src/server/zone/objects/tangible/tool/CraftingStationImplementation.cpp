/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "engine/engine.h"

#include "server/zone/objects/tangible/tool/CraftingStation.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "templates/tangible/tool/CraftingStationTemplate.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/building/BuildingObject.h"

void CraftingStationImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	if (!templateData->isCraftingStationTemplate()) {
		return;
	}

	CraftingStationTemplate* craftingStationData = dynamic_cast<CraftingStationTemplate*>(templateData);

	if (craftingStationData == nullptr) {
		return;
	}

	type = craftingStationData->getStationType();
	complexityLevel = craftingStationData->getComplexityLevel();
	hopperString = craftingStationData->getIngredientHopper();
}

void CraftingStationImplementation::notifyLoadFromDatabase() {
	TangibleObjectImplementation::notifyLoadFromDatabase();

	setLoggingName("CraftingStationObject");

	ManagedReference<SceneObject*> inputHopper = getSlottedObject("ingredient_hopper");

	if (inputHopper != nullptr) {
		Locker lock(inputHopper);

		inputHopper->setContainerDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
	}
}

void CraftingStationImplementation::createChildObjects() {
	if (hopperString != "") {
		ManagedReference<SceneObject*> ingredientHopper = server->getZoneServer()->createObject(hopperString.hashCode(), 1);

		if (ingredientHopper != nullptr) {
			if (!transferObject(ingredientHopper, 4, true)) {
				ingredientHopper->destroyObjectFromDatabase(true);
			} else {
				Locker hoplock(ingredientHopper);

				ingredientHopper->setContainerDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
			}
		}
	}
}

void CraftingStationImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);
	SceneObject* parent = getParent().get();

		if (parent != nullptr && parent->isCellObject()) {
			SceneObject* rootParent = getRootParent();

			if (rootParent != nullptr && rootParent->isBuildingObject()) {
				ManagedReference<BuildingObject*> building = cast<BuildingObject*>(rootParent);

				if (building != nullptr && !isASubChildOf(player)) {
					if (building->isOnAdminList(player)) {
						menuResponse->addRadialMenuItem(68, 3, "@ui_radial:craft_hopper_input"); // Input Hopper
					}
				}
			}
		}
}

int CraftingStationImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID == 68 && getSlottedObject("ingredient_hopper") != nullptr) {
		SceneObject* parent = getParent().get();

		if (parent != nullptr && parent->isCellObject()) {
			SceneObject* rootParent = getRootParent();

			if (rootParent != nullptr && rootParent->isBuildingObject()) {
				ManagedReference<BuildingObject*> building = cast<BuildingObject*>(rootParent);

				if (building != nullptr && !isASubChildOf(player)) {
					if (building->isOnAdminList(player)) {
						sendInputHopper(player);
					}
				}
			}
		}
	}

	return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

void CraftingStationImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("stationmod", Math::getPrecision(effectiveness, 2));
}

void CraftingStationImplementation::sendInputHopper(CreatureObject* player) {
	ManagedReference<SceneObject*> ingredientHopper = getSlottedObject("ingredient_hopper");

	if (ingredientHopper == nullptr || player == nullptr) {
		return;
	}

	player->executeObjectControllerAction(STRING_HASHCODE("opencontainer"), ingredientHopper->getObjectID(), "");
}

SceneObject* CraftingStationImplementation::findCraftingTool(CreatureObject* player) {
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	Locker inventoryLocker(inventory);

	SceneObject* craftingTool = nullptr;

	for (int i = 0; i < inventory->getContainerObjectsSize(); ++i) {
		SceneObject* object = inventory->getContainerObject(i);

		if (object != nullptr && object->isCraftingTool()) {
			CraftingTool* tool = cast<CraftingTool*>( object);

			if (!tool->isReady()) {
				continue;
			}

			int toolType = tool->getToolType();

			if (toolType == type) {
				return object;
			}

			if (toolType == CraftingTool::JEDI && type == CraftingTool::WEAPON) {
				craftingTool = object;
			}
		}

	}
	return craftingTool;
}

void CraftingStationImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	/// useModifer is the effectiveness

	effectiveness = values->getCurrentValue("usemodifier");
}
