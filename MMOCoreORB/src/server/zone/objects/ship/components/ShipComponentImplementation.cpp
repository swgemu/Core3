#include "server/zone/objects/ship/components/ShipComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/managers/ship/ShipManager.h"

void ShipComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<SharedTangibleObjectTemplate*>(templateData);

	if (shot != nullptr) {
		hitpoints = shot->getShipHitpoints();
		hitpointsMax = shot->getShipHitpoints();

		armor = shot->getShipArmor();
		armorMax = shot->getShipArmor();

		energyCost = shot->getShipEnergyConsumption();
		mass = shot->getShipMass();

		reverseEngineeringLevel = shot->getShipReverseEngineeringLevel();
	}

	const auto componentData = ShipManager::instance()->getShipComponentFromTemplate(templateData->getFullTemplateString());

	if (componentData != nullptr) {
		componentDataName = componentData->getName();
	}
}

void ShipComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
		const auto& attribute = values->getExperimentalPropertySubtitle(i);
		auto value = values->getCurrentValue(attribute);

		if (attribute == "energy_maintenance" || attribute == "ship_component_energy_required") {
			energyCost = value;
		} else if (attribute == "energy_efficiency") {
			energyEfficiency = value;
		} else if (attribute == "efficiency") {
			efficiency = value;
		} else if (attribute == "armorhpmax" || attribute == "ship_component_armor") {
			armorMax = value;
			armor = value;
		} else if (attribute == "hitpointsmax" || attribute == "ship_component_hitpoints") {
			hitpointsMax = value;
			hitpoints = value;
		} else if (attribute == "mass" || attribute == "ship_component_mass") {
			mass = value;
		}
	}
}

void ShipComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	alm->insertAttribute("@obj_attr_n:volume", volume);

	if (!craftersName.isEmpty()) {
		alm->insertAttribute("crafter", craftersName);
	}

	if (!objectSerial.isEmpty()) {
		alm->insertAttribute("serial_number", objectSerial);
	}

	StringBuffer msg;

	msg << Math::getPrecision(armor, 1) << "/" << Math::getPrecision(armorMax, 1);
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_armor", msg.toString());
	msg.deleteAll();

	msg << Math::getPrecision(hitpoints, 1) << "/" << Math::getPrecision(hitpointsMax, 1);
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_hitpoints", msg.toString());
	msg.deleteAll();

	if (getEnergyCost() != 0.f) {
		alm->insertAttribute("@obj_attr_n:ship_component.ship_component_energy_required", String::valueOf(Math::getPrecision(energyCost, 1)));
	}

	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_mass", String::valueOf(Math::getPrecision(mass, 1)));
}

void ShipComponentImplementation::addComponentFlag(uint32 value) {
	if (!(componentBitmask & value)) {
		componentBitmask |= value;
	}
}

void ShipComponentImplementation::removeComponentFlag(uint32 value) {
	if (componentBitmask & value) {
		componentBitmask &= ~value;
	}
}

void ShipComponentImplementation::install(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	auto ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	auto ship3 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 3) : nullptr;
	auto ship4 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 4) : nullptr;
	auto ship6 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 6) : nullptr;

	componentBitmask = 0;
	componentShip = ship;
	componentSlot = slot;

	uint8 command = DeltaMapCommands::ADD;

	ship->setComponentName(slot, getDisplayedName(), ship1, command);
	ship->setComponentMass(slot, mass, ship1, command);
	ship->setEnergyEfficiency(slot, energyEfficiency, ship1, command);
	ship->setEfficiency(slot, efficiency, ship1, command);
	ship->setEnergyCost(slot, energyCost, ship1, command);

	ship->setComponentMaxHitpoints(slot, hitpointsMax, ship3, command);
	ship->setComponentHitpoints(slot, hitpoints, ship3, command);
	ship->setComponentArmor(slot, armor, ship3, command);
	ship->setComponentMaxArmor(slot, armorMax, ship3, command);
	ship->setComponentOptions(slot, componentBitmask, ship3, command);

	ship->setChassisMass(ship->calculateCurrentMass(), false, ship4);

	ship->setComponentCRC(slot, getComponentDataName().hashCode(), ship6, command);

	if (notifyClient) {
		ship1->close();
		ship3->close();
		ship4->close();
		ship6->close();

		pilot->sendMessage(ship1);
		ship->broadcastMessage(ship3, true);
		pilot->sendMessage(ship4);
		ship->broadcastMessage(ship6, true);
	}
}

void ShipComponentImplementation::uninstall(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	auto ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	auto ship3 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 3) : nullptr;
	auto ship4 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 4) : nullptr;
	auto ship6 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 6) : nullptr;

	componentBitmask = 0;
	componentShip = nullptr;
	componentSlot = -1;

	int command = DeltaMapCommands::DROP;

	ship->setComponentName(slot, "", ship1, command);
	ship->setComponentMass(slot, 0.f, ship1, command);
	ship->setEnergyEfficiency(slot, 0.f, ship1, command);
	ship->setEfficiency(slot, 0.f, ship1, command);
	ship->setEnergyCost(slot, 0.f, ship1, command);

	ship->setComponentMaxHitpoints(slot, 0.f, ship3, command);
	ship->setComponentHitpoints(slot, 0.f, ship3, command);
	ship->setComponentArmor(slot, 0.f, ship3, command);
	ship->setComponentMaxArmor(slot, 0.f, ship3, command);
	ship->setComponentOptions(slot, 0, ship3, command);

	ship->setChassisMass(ship->calculateCurrentMass(), false, ship4);

	ship->setComponentCRC(slot, 0, ship6, command);

	if (notifyClient) {
		ship1->close();
		ship3->close();
		ship4->close();
		ship6->close();

		pilot->sendMessage(ship1);
		ship->broadcastMessage(ship3, true);
		pilot->sendMessage(ship4);
		ship->broadcastMessage(ship6, true);
	}
}
