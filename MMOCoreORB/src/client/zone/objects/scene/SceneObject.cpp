#include "SceneObject.h"
#include "../../managers/object/ObjectManager.h"
#include "../../Zone.h"

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

	arrangements.pop();

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

	info("created " + fullPath);
}

SceneObject::~SceneObject() {
	/*if (parent != NULL) {
		error("DELETING OBJECT WITH PARENT NOT NULL");
	}*/
	info("destroying object");

	if (slottedObjects.size() > 0)
		info("warning slottedObjects not 0 when destroying");

	if (containerObjects.size() > 0)
		info("warning slottedObjects not 0 when destroying");

	/*while (slottedObjects.size() > 0) {
		SceneObject* object = slottedObjects.get(0);

		removeObject(object);

		object->setParent(NULL);

		zone->getObjectManager()->destroyObject(object->getObjectID());
	}


	while (containerObjects.size() > 0) {
		SceneObject* object = containerObjects.get(0);
		object->setParent(NULL);

		containerObjects.drop(object->getObjectID());

		zone->getObjectManager()->destroyObject(object->getObjectID());
	}*/
}

bool SceneObject::transferObject(SceneObject* object, int containmentType) {
	info("adding object " + object->getLoggingName());

	if (containerType == 1) {
		int arrangementSize = object->getArrangementDescriptorSize();

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (slottedObjects.contains(childArrangement))
				return false;
		}

		for (int i = 0; i < arrangementSize; ++i) {
			slottedObjects.put(object->getArrangementDescriptor(i), object);
		}
	} else if (containerType == 2 || containerType == 3) {
		if (containerObjects.size() >= containerVolumeLimit)
			return false;

		if (containerObjects.contains(object->getObjectID()))
			return false;

		containerObjects.put(object->getObjectID(), object);
	} else {
		error("unkown container type");
		return false;
	}

	object->setParent(this);
	object->setContainmentType(containmentType);

	return true;
}

bool SceneObject::removeObject(SceneObject* object) {
	if (containerType == 1) {
		int arrangementSize = object->getArrangementDescriptorSize();

		for (int i = 0; i < arrangementSize; ++i) {
			String childArrangement = object->getArrangementDescriptor(i);

			if (slottedObjects.get(childArrangement) != object)
				return false;
		}

		for (int i = 0; i < arrangementSize; ++i)
			slottedObjects.drop(object->getArrangementDescriptor(i));
	} else if (containerType == 2 || containerType == 3) {
		if (!containerObjects.contains(object->getObjectID()))
			return false;

		containerObjects.drop(object->getObjectID());
	} else {
		error("unkown container type");
		return false;
	}

	object->setParent(NULL);

	/*if (notifyClient)
		broadcastMessage(object->link(0, 0xFFFFFFFF));*/

	return true;
}

