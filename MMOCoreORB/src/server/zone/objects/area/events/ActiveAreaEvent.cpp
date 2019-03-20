#include "ActiveAreaEvent.h"
#include "server/zone/objects/tangible/TangibleObject.h"

void ActiveAreaEvent::run() {
	auto area = activeArea.get();
	auto object = sceneObject.get();

	if (area == nullptr || object == nullptr)
		return;

	Locker clocker(object);

	Locker locker(area, object);

	switch (eventType) {
		case ENTEREVENT:
			area->notifyEnter(object);
			break;

		case EXITEVENT:
			area->notifyExit(object);
			break;

		default:
			break;
	}

	StringBuffer newName;
	newName << area->getLoggingName() << " ran event type " << eventType << " on " << object->getLoggingName();

	auto tano = object->asTangibleObject();

	if (tano != nullptr) {
		newName << " with final area count " << tano->getActiveAreasSize();
	}

	setTaskName(newName.toString().toCharArray());
}

