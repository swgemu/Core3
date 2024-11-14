#include "server/zone/objects/ship/components/ShipCapacitorComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/DeltaMessage.h"

void ShipCapacitorComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<ShipComponentTemplate*>(templateData);

	if (shot != nullptr) {
		const auto& attributeMap = shot->getAttributeMap();

		for (int i = 0; i < attributeMap.size(); ++i) {
			const auto& attribute = attributeMap.elementAt(i).getKey();
			float value = attributeMap.elementAt(i).getValue();

			if (attribute == "maxEnergy") {
				capacitorEnergy = value;
			} else if (attribute == "rechargeRate") {
				capacitorRechargeRate = value;
			}
		}
	}
}

void ShipCapacitorComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getTotalExperimentalAttributes(); ++i) {
		const auto& attribute = values->getAttribute(i);
		auto value = values->getCurrentValue(attribute);

		if (attribute == "ship_component_capacitor_energy") {
			capacitorEnergy = value;
		} else if (attribute == "ship_component_capacitor_energy_recharge_rate") {
			capacitorRechargeRate = value;
		}
	}
}

void ShipCapacitorComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ShipComponentImplementation::fillAttributeList(alm, object);

	StringBuffer msg;

	msg << "0.0/" << Math::getPrecision(capacitorEnergy, 1);
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_capacitor_energy", msg.toString());

	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_capacitor_energy_recharge_rate", String::valueOf(Math::getPrecision(capacitorRechargeRate, 1)));

	if (reverseEngineeringLevel != 0) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", reverseEngineeringLevel);
	}
}

void ShipCapacitorComponentImplementation::install(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::install(pilot, ship, slot, notifyClient);

	auto deltaVector = notifyClient ? ship->getDeltaVector() : nullptr;

	ship->setCapacitorRechargeRate(capacitorRechargeRate, false, nullptr, deltaVector);
	ship->setCapacitorMaxEnergy(capacitorEnergy, false, nullptr, deltaVector);

	ship->setCapacitorEnergy(capacitorEnergy, false, nullptr, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship);
	}
}

void ShipCapacitorComponentImplementation::uninstall(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);

	auto deltaVector = notifyClient ? ship->getDeltaVector() : nullptr;

	ship->setCapacitorRechargeRate(0.f, false, nullptr, deltaVector);
	ship->setCapacitorMaxEnergy(0.f, false, nullptr, deltaVector);

	ship->setCapacitorEnergy(0.f, false, nullptr, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship);
	}
}
