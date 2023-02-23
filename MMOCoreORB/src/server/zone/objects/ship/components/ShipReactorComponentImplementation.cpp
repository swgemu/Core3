#include "server/zone/objects/ship/components/ShipReactorComponent.h"
#include "server/zone/objects/ship/components/ShipComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "templates/tangible/SharedShipObjectTemplate.h"
#include "server/zone/packets/DeltaMessage.h"

void ShipReactorComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<SharedTangibleObjectTemplate*>(templateData);

	if (shot != nullptr) {
		reactorGenerationRate = shot->getShipMaxEnergy();
	}
}

void ShipReactorComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	if(values->hasProperty("ship_component_reactor_generation_rate")) {
		reactorGenerationRate = values->getCurrentValue("ship_component_reactor_generation_rate");
	}
}

void ShipReactorComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ShipComponentImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_reactor_generation_rate", String::valueOf(Math::getPrecision(reactorGenerationRate, 1)));

	if (craftersName.isEmpty()) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", getReverseEngineeringLevel());
	}
}

void ShipReactorComponentImplementation::install(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::install(pilot, ship, slot, notifyClient);

	DeltaMessage* ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;

	ship->setReactorGenerationRate(reactorGenerationRate, false, ship1);

	if (notifyClient) {
		ship1->close();

		pilot->sendMessage(ship1);
	}
}

void ShipReactorComponentImplementation::uninstall(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);

	DeltaMessage* ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;

	ship->setReactorGenerationRate(0.f, false, ship1);

	if (notifyClient) {
		ship1->close();

		pilot->sendMessage(ship1);
	}
}
