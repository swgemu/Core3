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
}

void CraftingStationImplementation::notifyLoadFromDatabase() {
	TangibleObjectImplementation::notifyLoadFromDatabase();

	setLoggingName("CraftingStationObject");

	ManagedReference<SceneObject*> inputHopper = getSlottedObject("ingredient_hopper");

	if (inputHopper != nullptr) {
		ContainerPermissions* permissions = inputHopper->getContainerPermissionsForUpdate();
		permissions->setOwner(getObjectID());
		permissions->setInheritPermissionsFromParent(true);
		permissions->setDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
		permissions->setDenyPermission("owner", ContainerPermissions::MOVECONTAINER);
	}
}

void CraftingStationImplementation::createChildObjects() {
	ZoneServer* zoneServer = server->getZoneServer();

	if (zoneServer == nullptr) {
		return;
	}

	for (int i = 0; i < templateObject->getChildObjectsSize(); ++i) {
		const ChildObject* child = templateObject->getChildObject(i);

		if (child == nullptr) {
			continue;
		}

		ManagedReference<SceneObject*> hopper = zoneServer->createObject(child->getTemplateFile().hashCode(), 1);

		if (hopper == nullptr) {
			continue;
		}

		if (!transferObject(hopper, child->getContainmentType())) {
			hopper->destroyObjectFromDatabase(true);
			continue;
		}

		ContainerPermissions* permissions = hopper->getContainerPermissionsForUpdate();
		permissions->setOwner(getObjectID());
		permissions->setInheritPermissionsFromParent(true);
		permissions->setDefaultDenyPermission(ContainerPermissions::MOVECONTAINER);
		permissions->setDenyPermission("owner", ContainerPermissions::MOVECONTAINER);

		childObjects.put(hopper);

		hopper->initializeChildObject(_this.getReferenceUnsafeStaticCast());
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
	if (selectedID == 68) {
		if (getSlottedObject("ingredient_hopper") == nullptr && !getObjectNameStringIdName().contains("public")) {
			createChildObjects();
		}

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
	// usemodifier is the effectiveness
	effectiveness = values->getCurrentValue("usemodifier");
}
