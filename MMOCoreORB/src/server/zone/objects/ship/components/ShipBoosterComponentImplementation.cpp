#include "server/zone/objects/ship/components/ShipBoosterComponent.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "templates/tangible/SharedShipObjectTemplate.h"

void ShipBoosterComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<SharedTangibleObjectTemplate*>(templateData);

	if (shot != nullptr) {
		boosterConsumptionRate = shot->getBoosterEnergyConsumptionRate();
		boosterAcceleration = shot->getBoosterAcceleration();
		boosterEnergy = shot->getShipMaxEnergy();
		boosterRechargeRate = shot->getShipRechargeRate();
		boosterSpeed = shot->getShipSpeed();
	}
}

void ShipBoosterComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
		auto attribute = values->getExperimentalPropertySubtitle(i);
		auto value = values->getCurrentValue(attribute);

		if (attribute == "ship_component_booster_energy_consumption_rate") {
			boosterConsumptionRate = value;
		} else if(attribute == "ship_component_booster_acceleration") {
			boosterAcceleration = value;
		} else if (attribute == "ship_component_booster_energy") {
			boosterEnergy = value;
		} else if (attribute == "ship_component_booster_energy_recharge_rate") {
			boosterRechargeRate = value;
		} else if (attribute == "ship_component_booster_speed_maximum") {
			boosterSpeed = value;
		}
	}
}

void ShipBoosterComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ShipComponentImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_energy", String::valueOf(Math::getPrecision(boosterEnergy, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_energy_recharge_rate", String::valueOf(Math::getPrecision(boosterRechargeRate, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_energy_consumption_rate", String::valueOf(Math::getPrecision(boosterConsumptionRate, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_acceleration", String::valueOf(Math::getPrecision(boosterAcceleration, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_speed_maximum", String::valueOf(Math::getPrecision(boosterSpeed, 1)));

	if (craftersName.isEmpty()) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", getReverseEngineeringLevel());
	}
}

void ShipBoosterComponentImplementation::install(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::install(pilot, ship, slot, notifyClient);

	DeltaMessage* ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	DeltaMessage* ship4 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 4) : nullptr;

	ship->setBoosterMaxSpeed(boosterSpeed, false, ship1);
	ship->setBoosterMaxEnergy(boosterEnergy, false, ship1);
	ship->setBoosterEnergyConsumptionRate(boosterConsumptionRate, false, ship1);
	ship->setBoosterAcceleration(boosterAcceleration, false, ship1);
	ship->setBoosterRechargeRate(boosterRechargeRate, false, ship1);

	ship->setBoosterEnergy(boosterEnergy, false, ship4);

	if (notifyClient) {
		ship1->close();
		ship4->close();

		pilot->sendMessage(ship1);
		pilot->sendMessage(ship4);
	}
}

void ShipBoosterComponentImplementation::uninstall(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);

	DeltaMessage* ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	DeltaMessage* ship4 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 4) : nullptr;

	ship->setBoosterMaxSpeed(0.f, false, ship1);
	ship->setBoosterMaxEnergy(0.f, false, ship1);
	ship->setBoosterEnergyConsumptionRate(0.f, false, ship1);
	ship->setBoosterAcceleration(0.f, false, ship1);
	ship->setBoosterRechargeRate(0.f, false, ship1);

	ship->setBoosterEnergy(0.f, false, ship4);

	if (notifyClient) {
		ship1->close();
		ship4->close();

		pilot->sendMessage(ship1);
		pilot->sendMessage(ship4);
	}
}
