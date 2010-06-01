/*
 * SharedObjectTemplate.cpp
 *
 *  Created on: 30/04/2010
 *      Author: victor
 */

#include "SharedObjectTemplate.h"

void SharedObjectTemplate::readObject(LuaObject* templateData) {
	objectName = templateData->getStringField("objectName");
	detailedDescription = templateData->getStringField("detailedDescription");
	lookAtText = templateData->getStringField("lookAtText");

	snapToTerrain = templateData->getByteField("snapToTerrain");
	containerType = templateData->getIntField("containerType");
	containerVolumeLimit = templateData->getIntField("containerVolumeLimit");

	tintPallete = templateData->getStringField("tintPallete");

	LuaObject arrangements = templateData->getObjectField("arrangementDescriptors");

	for (int i = 1; i <= arrangements.getTableSize(); ++i) {
		arrangementDescriptors.add(arrangements.getStringAt(i));
	}

	arrangements.pop();

	LuaObject slots = templateData->getObjectField("slotDescriptors");

	for (int i = 1; i <= slots.getTableSize(); ++i) {
		slotDescriptors.add(slots.getStringAt(i));
	}

	slots.pop();

	appearanceFilename = templateData->getStringField("appearanceFilename");
	portalLayoutFilename = templateData->getStringField("portalLayoutFilename");

	totalCellNumber = templateData->getIntField("totalCellNumber");

	clientDataFile = templateData->getStringField("clientDataFile");

	collisionMaterialFlags = templateData->getIntField("collisionMaterialFlags");
	collisionMaterialPassFlags = templateData->getIntField("collisionMaterialPassFlags");
	scale = templateData->getFloatField("scale");

	collisionMaterialBlockFlags = templateData->getIntField("collisionMaterialBlockFlags");
	collisionActionFlags = templateData->getIntField("collisionActionFlags");
	collisionActionPassFlags = templateData->getIntField("collisionActionPassFlags");
	collisionActionBlockFlags = templateData->getIntField("collisionActionBlockFlags");
	gameObjectType = templateData->getIntField("gameObjectType");

	sendToClient = templateData->getByteField("sendToClient");
	scaleThresholdBeforeExtentTest = templateData->getFloatField("scaleThresholdBeforeExtentTest");
	clearFloraRadius = templateData->getFloatField("clearFloraRadius");
	surfaceType = templateData->getIntField("surfaceType");
	noBuildRadius = templateData->getFloatField("noBuildRadius");
	onlyVisibleInTools = templateData->getByteField("onlyVisibleInTools");
	locationReservationRadius = templateData->getFloatField("locationReservationRadius");
	clientObjectCRC = templateData->getIntField("clientObjectCRC");

	templateType = templateData->getIntField("templateType");
}
