#include "server/zone/objects/ship/components/ShipArmorComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/DeltaMessage.h"

void ShipArmorComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);
}

void ShipArmorComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ShipComponentImplementation::fillAttributeList(alm, object);

	if (reverseEngineeringLevel != 0) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", reverseEngineeringLevel);
	}
}

void ShipArmorComponentImplementation::install(CreatureObject* pilot, ShipObject *ship, int slot, bool notifyClient) {
	ShipComponentImplementation::install(pilot, ship, slot, notifyClient);
}

void ShipArmorComponentImplementation::uninstall(CreatureObject* pilot, ShipObject *ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);
}
