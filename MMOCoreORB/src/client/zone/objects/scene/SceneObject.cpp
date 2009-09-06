#include "SceneObject.h"

SceneObject::SceneObject(LuaObject* templateData) : Logger("SceneObject") {
	parent = NULL;

	objectID = 0;

	slottedObjects.setNullValue(NULL);
	objectName.setStringId(String(templateData->getStringField("objectName")));

	detailedDescription.setStringId(String(templateData->getStringField("detailedDescription")));

	containerType = templateData->getIntField("containerType");
	containerVolumeLimit = templateData->getIntField("containerVolumeLimit");

	gameObjectType = templateData->getIntField("gameObjectType");

	objectCRC = templateData->getIntField("clientObjectCRC");

	LuaObject arrangements = templateData->getObjectField("arrangementDescriptors");

	for (int i = 1; i <= arrangements.getTableSize(); ++i) {
		arrangementDescriptors.add(arrangements.getStringAt(i));
	}

	arrangements.pop();void parseBaseline(uint8 type, BaseMessage* message);

	LuaObject slots = templateData->getObjectField("slotDescriptors");

	for (int i = 1; i <= slots.getTableSize(); ++i) {
		slotDescriptors.add(slots.getStringAt(i));
	}

	slots.pop();

	containmentType = 4;

	initializePosition(0.f, 0.f, 0.f);

	movementCounter = 0;

	setGlobalLogging(true);
	setLogging(false);

	String fullPath;
	objectName.getFullPath(fullPath);

	client = NULL;

	info("created " + fullPath, true);
}

