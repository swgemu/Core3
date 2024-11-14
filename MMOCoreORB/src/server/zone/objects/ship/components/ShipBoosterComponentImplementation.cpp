#include "server/zone/objects/ship/components/ShipBoosterComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/DeltaMessage.h"

void ShipBoosterComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<ShipComponentTemplate*>(templateData);

	if (shot != nullptr) {
		const auto& attributeMap = shot->getAttributeMap();

		for (int i = 0; i < attributeMap.size(); ++i) {
			const auto& attribute = attributeMap.elementAt(i).getKey();
			float value = attributeMap.elementAt(i).getValue();

			if (attribute == "consumptionRate") {
				boosterConsumptionRate = value;
			} else if(attribute == "acceleration") {
				boosterAcceleration = value;
			} else if (attribute == "maximumEnergy") {
				boosterEnergy = value;
			} else if (attribute == "rechargeRate") {
				boosterRechargeRate = value;
			} else if (attribute == "maxSpeed") {
				boosterSpeed = value;
			}
		}
	}
}

void ShipBoosterComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getTotalExperimentalAttributes(); ++i) {
		const auto& attribute = values->getAttribute(i);
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

	StringBuffer msg;

	msg << "0.0/" << Math::getPrecision(boosterEnergy, 1);
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_energy", msg.toString());

	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_energy_recharge_rate", String::valueOf(Math::getPrecision(boosterRechargeRate, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_energy_consumption_rate", String::valueOf(Math::getPrecision(boosterConsumptionRate, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_acceleration", String::valueOf(Math::getPrecision(boosterAcceleration, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_speed_maximum", String::valueOf(Math::getPrecision(boosterSpeed, 1)));

	if (reverseEngineeringLevel != 0) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", reverseEngineeringLevel);
	}
}

void ShipBoosterComponentImplementation::install(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::install(pilot, ship, slot, notifyClient);

	auto deltaVector = notifyClient ? ship->getDeltaVector() : nullptr;

	ship->setBoosterMaxSpeed(boosterSpeed, false, nullptr, deltaVector);
	ship->setBoosterMaxEnergy(boosterEnergy, false, nullptr, deltaVector);
	ship->setBoosterEnergyConsumptionRate(boosterConsumptionRate, false, nullptr, deltaVector);
	ship->setBoosterAcceleration(boosterAcceleration, false, nullptr, deltaVector);
	ship->setBoosterRechargeRate(boosterRechargeRate, false, nullptr, deltaVector);

	ship->setBoosterEnergy(boosterEnergy, false, nullptr, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship);
	}
}

void ShipBoosterComponentImplementation::uninstall(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);

	auto deltaVector = notifyClient ? ship->getDeltaVector() : nullptr;

	ship->setBoosterMaxSpeed(0.f, false, nullptr, deltaVector);
	ship->setBoosterMaxEnergy(0.f, false, nullptr, deltaVector);
	ship->setBoosterEnergyConsumptionRate(0.f, false, nullptr, deltaVector);
	ship->setBoosterAcceleration(0.f, false, nullptr, deltaVector);
	ship->setBoosterRechargeRate(0.f, false, nullptr, deltaVector);

	ship->setBoosterEnergy(0.f, false, nullptr, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship);
	}
}
