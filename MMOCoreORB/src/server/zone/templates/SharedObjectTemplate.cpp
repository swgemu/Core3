/*
 * SharedObjectTemplate.cpp
 *
 *  Created on: 30/04/2010
 *      Author: victor
 */

#include "SharedObjectTemplate.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/planet/PlanetManager.h"

#include "server/zone/templates/slots/SlotDescriptor.h"
#include "server/zone/templates/slots/ArrangementDescriptor.h"

#include "server/ServerCore.h"

void SharedObjectTemplate::readObject(LuaObject* templateData) {
	TemplateManager* templateManager = TemplateManager::instance();

	objectName = templateData->getStringField("objectName");
	detailedDescription = templateData->getStringField("detailedDescription");
	lookAtText = templateData->getStringField("lookAtText");

	snapToTerrain = templateData->getByteField("snapToTerrain");
	containerType = templateData->getIntField("containerType");
	containerVolumeLimit = templateData->getIntField("containerVolumeLimit");

	tintPallete = templateData->getStringField("tintPallete");

	String arrangementDescriptorFilename = templateData->getStringField("arrangementDescriptorFilename");

	Reference<ArrangementDescriptor*> arrangementDescriptor = templateManager->getArrangementDescriptor(arrangementDescriptorFilename);

	if (arrangementDescriptor != NULL)
		arrangementDescriptor->clone(arrangementDescriptors);

	String slotDescriptorFilename = templateData->getStringField("slotDescriptorFilename");

	Reference<SlotDescriptor*> slotDescriptor = templateManager->getSlotDescriptor(slotDescriptorFilename);

	if (slotDescriptor != NULL)
		slotDescriptor->clone(slotDescriptors);

	appearanceFilename = templateData->getStringField("appearanceFilename");
	appearanceTemplate = NULL;
	portalLayoutFilename = templateData->getStringField("portalLayoutFilename");
	portalLayout = NULL;

	zoneComponent = templateData->getStringField("zoneComponent");
	objectMenuComponent = templateData->getStringField("objectMenuComponent");
	containerComponent = templateData->getStringField("containerComponent");

	totalCellNumber = templateData->getIntField("totalCellNumber");

	clientDataFile = templateData->getStringField("clientDataFile");

	collisionMaterialFlags = templateData->getIntField("collisionMaterialFlags");
	collisionMaterialPassFlags = templateData->getIntField("collisionMaterialPassFlags");

	LuaObject scaleObject = templateData->getObjectField("scale");

	if (scaleObject.isValidTable()) {
		scale.removeAll(2, 0);

		for (int i = 1; i <= scaleObject.getTableSize(); ++i) {
			scale.add(scaleObject.getFloatAt(i));
		}

		scaleObject.pop();
	} else {
		scaleObject.pop();

		scale.add(templateData->getFloatField("scale"));
	}

	collisionMaterialBlockFlags = templateData->getIntField("collisionMaterialBlockFlags");
	collisionActionFlags = templateData->getIntField("collisionActionFlags");
	collisionActionPassFlags = templateData->getIntField("collisionActionPassFlags");
	collisionActionBlockFlags = templateData->getIntField("collisionActionBlockFlags");
	gameObjectType = templateData->getIntField("gameObjectType");
	clientGameObjectType = templateData->getIntField("clientGameObjectType");

	sendToClient = templateData->getByteField("sendToClient");
	scaleThresholdBeforeExtentTest = templateData->getFloatField("scaleThresholdBeforeExtentTest");
	clearFloraRadius = templateData->getFloatField("clearFloraRadius");
	surfaceType = templateData->getIntField("surfaceType");
	noBuildRadius = templateData->getFloatField("noBuildRadius");
	onlyVisibleInTools = templateData->getByteField("onlyVisibleInTools");
	locationReservationRadius = templateData->getFloatField("locationReservationRadius");
	clientObjectCRC = templateData->getIntField("clientObjectCRC");

	templateType = templateData->getIntField("templateType");

	planetMapCategory = templateManager->getPlanetMapCategoryByName(templateData->getStringField("planetMapCategory"));
	planetMapSubCategory = templateManager->getPlanetMapCategoryByName(templateData->getStringField("planetMapSubCategory"));

	LuaObject luaItemList = templateData->getObjectField("childObjects");

	int size = luaItemList.getTableSize();

	lua_State* L = luaItemList.getLuaState();

	for (int i = 0; i < size; ++i) {
		lua_rawgeti(L, -1, i + 1);
		LuaObject a(L);

		ChildObject object;
		object.parseFromLua(&a);

		childObjects.add(object);

		a.pop();
	}

	luaItemList.pop();
}

PortalLayout* SharedObjectTemplate::getPortalLayout() {
	if (portalLayout != NULL)
		return portalLayout;
	else if (!loadedPortalLayout) {
		loadedPortalLayout = true;

		if (portalLayoutFilename.length() > 1) {
			try {
				portalLayout = TemplateManager::instance()->getPortalLayout(portalLayoutFilename);
			} catch(Exception& e) {
				e.printStackTrace();
			}
		}
	}

	return portalLayout;
}

AppearanceTemplate* SharedObjectTemplate::getAppearanceTemplate() {
	if (appearanceTemplate != NULL)
		return appearanceTemplate;
	else if (!loadedAppearanceTemplate) {
		loadedAppearanceTemplate = true;

		if (appearanceFilename.length() > 1) {
			try {
				appearanceTemplate = TemplateManager::instance()->getAppearanceTemplate(appearanceFilename);
			} catch(Exception& e) {
				e.printStackTrace();
			}
		}
	}

	return appearanceTemplate;
}
