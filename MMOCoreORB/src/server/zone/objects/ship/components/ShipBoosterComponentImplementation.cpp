#include "server/zone/objects/ship/components/ShipBoosterComponent.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/ship/ShipObject.h"


void ShipBoosterComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);
	SharedTangibleObjectTemplate *tmpl = static_cast<SharedTangibleObjectTemplate*>(templateData);
	if (tmpl == nullptr) {
		error("nullptr Template");
	}

	energyConsumptionRate = tmpl->getBoosterEnergyConsumptionRate();
	boosterAcceleration = tmpl->getBoosterAcceleration();
	boosterEnergy = tmpl->getShipMaxEnergy();
	boosterRechargeRate = tmpl->getShipRechargeRate();
	boosterSpeed = tmpl->getShipSpeed();
}

void ShipBoosterComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
		String attribute = values->getExperimentalPropertySubtitle(i);
		float min = values->getMinValue(attribute);
		float max = values->getMaxValue(attribute);
		float current = values->getCurrentValue(attribute);

		if (attribute == "ship_component_booster_energy_consumption_rate") {
			energyConsumptionRate = (min + max) + current;
		} else if(attribute == "ship_component_booster_acceleration") {
			boosterAcceleration = current;
		} else if (attribute == "ship_component_booster_energy") {
			boosterEnergy = current;
		} else if (attribute == "ship_component_booster_energy_recharge_rate") {
			boosterRechargeRate = current;
		} else if (attribute == "ship_component_booster_speed_maximum") {
			boosterSpeed = current;
		}

	}

	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);
}



void ShipBoosterComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ShipComponentImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("ship_component_booster_energy", String::valueOf(Math::getPrecision(boosterEnergy, 1)));
	alm->insertAttribute("ship_component_booster_energy_recharge_rate", String::valueOf(Math::getPrecision(boosterRechargeRate, 1)));
	alm->insertAttribute("ship_component_booster_energy_consumption_rate", String::valueOf(Math::getPrecision(energyConsumptionRate, 1)));
	alm->insertAttribute("ship_component_booster_acceleration", String::valueOf(Math::getPrecision(boosterAcceleration, 1)));
	alm->insertAttribute("ship_component_booster_speed_maximum", String::valueOf(Math::getPrecision(boosterSpeed, 1)));
}

void ShipBoosterComponentImplementation::install(CreatureObject* owner, ShipObject* ship, int slot, bool notifyClient) {
	DeltaMessage* message = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;

	ship->setBoosterMaxSpeed(boosterSpeed, notifyClient, message);
	ship->setBoosterMaxEnergy(boosterEnergy, notifyClient, message);
	ship->setBoosterEnergyConsumptionRate(energyConsumptionRate, notifyClient, message);
	ship->setBoosterAcceleration(boosterAcceleration, notifyClient, message);
	ship->setBoosterRechargeRate(boosterRechargeRate, notifyClient, message);
	ship->setEnergyCost(slot, getEnergyCost(), message);

	DeltaMessage* message2 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 3) : nullptr;

	ship->setComponentMaxHitpoints(slot, getMaxHitpoints(), message2);
	ship->setComponentHitpoints(slot, getHitpoints(), message2);
	ship->setComponentArmor(slot, getArmor(), message2);
	ship->setComponentMaxArmor(slot, getMaxArmor(), message2);

	if (notifyClient) {
		message->close();
		message2->close();
		owner->sendMessage(message);
		owner->sendMessage(message2);
	}

	ship->setBoosterEnergy(boosterEnergy, notifyClient);
}
