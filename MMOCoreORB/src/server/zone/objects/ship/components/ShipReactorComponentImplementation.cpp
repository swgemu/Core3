#include "server/zone/objects/ship/components/ShipReactorComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/DeltaMessage.h"

void ShipReactorComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<ShipComponentTemplate*>(templateData);

	if (shot != nullptr) {
		const auto& attributeMap = shot->getAttributeMap();

		for (int i = 0; i < attributeMap.size(); ++i) {
			const auto& attribute = attributeMap.elementAt(i).getKey();
			float value = attributeMap.elementAt(i).getValue();

			if (attribute == "energyGeneration") {
				reactorGenerationRate = value;
			}
		}
	}
}

void ShipReactorComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	if (values->hasExperimentalAttribute("ship_component_reactor_generation_rate")) {
		reactorGenerationRate = values->getCurrentValue("ship_component_reactor_generation_rate");
	}
}

void ShipReactorComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ShipComponentImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_reactor_generation_rate", String::valueOf(Math::getPrecision(reactorGenerationRate, 1)));

	if (reverseEngineeringLevel != 0) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", reverseEngineeringLevel);
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
