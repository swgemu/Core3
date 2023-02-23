#include "server/zone/objects/ship/components/ShipCapacitorComponent.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

void ShipCapacitorComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<SharedTangibleObjectTemplate*>(templateData);

	if (shot != nullptr) {
		capacitorEnergy = shot->getShipMaxEnergy();
		capacitorRechargeRate = shot->getShipRechargeRate();
	}
}

void ShipCapacitorComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
		const String& attribute = values->getExperimentalPropertySubtitle(i);
		float value = values->getCurrentValue(attribute);

		if (attribute == "ship_component_capacitor_energy") {
			capacitorEnergy = value;
		} else if (attribute == "ship_component_capacitor_energy_recharge_rate") {
			capacitorRechargeRate = value;
		}
	}
}

void ShipCapacitorComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ShipComponentImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_capacitor_energy", String::valueOf(Math::getPrecision(capacitorEnergy, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_capacitor_energy_recharge_rate", String::valueOf(Math::getPrecision(capacitorRechargeRate, 1)));

	if (craftersName.isEmpty()) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", getReverseEngineeringLevel());
	}
}

void ShipCapacitorComponentImplementation::install(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::install(pilot, ship, slot, notifyClient);

	DeltaMessage* ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	DeltaMessage* ship4 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 4) : nullptr;

	ship->setCapacitorRechargeRate(capacitorRechargeRate, false, ship1);
	ship->setCapacitorMaxEnergy(capacitorEnergy, false, ship1);

	ship->setCapacitorEnergy(capacitorEnergy, false, ship4);

	if (notifyClient) {
		ship1->close();
		ship4->close();

		pilot->sendMessage(ship1);
		pilot->sendMessage(ship4);
	}
}

void ShipCapacitorComponentImplementation::uninstall(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);

	DeltaMessage* ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	DeltaMessage* ship4 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 4) : nullptr;

	ship->setCapacitorRechargeRate(0.f, false, ship1);
	ship->setCapacitorMaxEnergy(0.f, false, ship1);

	ship->setCapacitorEnergy(0.f, false, ship4);

	if (notifyClient) {
		ship1->close();
		ship4->close();

		pilot->sendMessage(ship1);
		pilot->sendMessage(ship4);
	}
}
