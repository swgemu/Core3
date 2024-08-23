#include "server/zone/objects/ship/components/ShipDroidInterfaceComponent.h"
#include "server/zone/objects/ship/ShipObject.h"

void ShipDroidInterfaceComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<ShipComponentTemplate*>(templateData);

	if (shot != nullptr) {
		const auto& attributeMap = shot->getAttributeMap();

		for (int i = 0; i < attributeMap.size(); ++i) {
			const auto& attribute = attributeMap.elementAt(i).getKey();
			float value = attributeMap.elementAt(i).getValue();

			if (attribute == "commandSpeed") {
				droidCommandSpeed = value;
			}
		}
	}
}

void ShipDroidInterfaceComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getTotalExperimentalAttributes(); ++i) {
		const auto& attribute = values->getAttribute(i);
		auto value = values->getCurrentValue(attribute);

		if (attribute == "ship_component_droidinterface_speed") {
			droidCommandSpeed = value;
		}
	}
}

void ShipDroidInterfaceComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ShipComponentImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_droidinterface_speed", droidCommandSpeed);

	if (reverseEngineeringLevel != 0) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", reverseEngineeringLevel);
	}
}

void ShipDroidInterfaceComponentImplementation::install(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::install(pilot, ship, slot, notifyClient);

	ship->setDroidCommandSpeed(droidCommandSpeed, notifyClient);
}

void ShipDroidInterfaceComponentImplementation::uninstall(CreatureObject* pilot, ShipObject *ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);

	ship->setDroidCommandSpeed(0.f, notifyClient);
}
