
#include "GarageDataComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/area/ActiveArea.h"

void GarageDataComponent::notifyObjectdestroyingFromDatabase() {
	if (garageArea != NULL)
		garageArea->destroyObjectFromDatabase(true);
}

void GarageDataComponent::createGarageArea() {
	float positionX = parent.get()->getPositionX();
	float positionY = parent.get()->getPositionY();
	float positionZ = parent.get()->getPositionZ();

	uint32 garageAreaTemplateCRC = String("object/garage_area.iff").hashCode();
	ManagedReference<SceneObject*> obj = parent.get()->getZoneServer()->createObject(garageAreaTemplateCRC, 1);

	if (obj == NULL)
		return;

	ActiveArea* activeArea = cast<ActiveArea*>(obj.get());

	activeArea->setRadius(64);
	activeArea->initializePosition(positionX, positionZ, positionY);
	parent.get()->getZone()->transferObject(activeArea, -1, true);

	garageArea = activeArea;
}

ManagedReference<ActiveArea*> GarageDataComponent::getGarageArea() {
	return garageArea;
}
