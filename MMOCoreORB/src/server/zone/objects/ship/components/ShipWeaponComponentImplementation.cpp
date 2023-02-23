#include "server/zone/objects/ship/components/ShipWeaponComponent.h"
#include "server/zone/objects/ship/components/ShipComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "templates/tangible/SharedShipObjectTemplate.h"
#include "server/zone/packets/DeltaMessage.h"

void ShipWeaponComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<SharedTangibleObjectTemplate*>(templateData);

	if (shot != nullptr) {
		maxDamage = shot->getWeaponMaxDamage();
		minDamage = shot->getWeaponMinDamage();
		shieldEffectiveness = shot->getWeaponShieldEffectiveness() * 0.1f;
		armorEffectiveness = shot->getWeaponArmorEffectiveness() * 0.1f;
		energyPerShot = shot->getEnergyPerShot();
		refireRate = shot->getWeaponRefireRate() * 0.1f;
	}
}

void ShipWeaponComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
		String attribute = values->getExperimentalPropertySubtitle(i);
		float value = values->getCurrentValue(attribute);

		if (attribute == "damage_max" || attribute == "ship_component_weapon_damage_maximum") {
			maxDamage = value;
		} else if (attribute == "damage_min" || attribute == "ship_component_weapon_damage_minimum") {
			minDamage = value;
		} else if (attribute == "effective_shields" || attribute == "ship_component_weapon_effectiveness_shields") {
			shieldEffectiveness = value * 0.001f;
		} else if (attribute == "effective_armor" || attribute == "ship_component_weapon_effectiveness_armor") {
			armorEffectiveness = value * 0.001f;
		} else if (attribute == "ship_component_weapon_energy_per_shot") {
			energyPerShot = value;
		} else if (attribute == "ship_component_weapon_refire_rate") {
			refireRate = values->getCurrentValue(attribute) * 0.001f;
		}
	}
}

void ShipWeaponComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ShipComponentImplementation::fillAttributeList(alm, object);

	StringBuffer display;
	display << Math::getPrecision(minDamage, 3) << " - " << Math::getPrecision(maxDamage, 3);

	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_weapon_damage", display.toString());
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_weapon_effectiveness_shields", String::valueOf(Math::getPrecision(shieldEffectiveness, 3)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_weapon_effectiveness_armor", String::valueOf(Math::getPrecision(armorEffectiveness, 3)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_weapon_energy_per_shot", String::valueOf(Math::getPrecision(energyPerShot, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_weapon_refire_rate", String::valueOf(Math::getPrecision(refireRate, 3)));

	if (craftersName.isEmpty()) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", getReverseEngineeringLevel());
	}
}

void ShipWeaponComponentImplementation::install(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::install(pilot, ship, slot, notifyClient);

	DeltaMessage* ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	DeltaMessage* ship4 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 4) : nullptr;

	int command = DeltaMapCommands::ADD;

	ship->setMaxDamage(slot, maxDamage, ship1, command);
	ship->setMinDamage(slot, minDamage, ship1, command);
	ship->setShieldEffectiveness(slot, shieldEffectiveness, ship1, command);
	ship->setArmorEffectiveness(slot, armorEffectiveness, ship1, command);
	ship->setEnergyPerShot(slot, energyPerShot, ship1, command);
	ship->setRefireRate(slot, refireRate, ship1, command);

	ship->setRefireEfficiency(slot, 1.f, ship4, command);

	if (notifyClient) {
		ship1->close();
		ship4->close();

		pilot->sendMessage(ship1);
		pilot->sendMessage(ship4);
	}
}

void ShipWeaponComponentImplementation::uninstall(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);

	DeltaMessage* ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	DeltaMessage* ship4 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 4) : nullptr;

	int command = DeltaMapCommands::DROP;

	ship->setMaxDamage(slot, 0.f, ship1, command);
	ship->setMinDamage(slot, 0.f, ship1, command);
	ship->setShieldEffectiveness(slot, 0.f, ship1, command);
	ship->setArmorEffectiveness(slot, 0.f, ship1, command);
	ship->setEnergyPerShot(slot, 0.f, ship1, command);
	ship->setRefireRate(slot, 0.f, ship1, command);

	ship->setRefireEfficiency(slot, 0.f, ship4, command);

	if (notifyClient) {
		ship1->close();
		ship4->close();

		pilot->sendMessage(ship1);
		pilot->sendMessage(ship4);
	}
}
