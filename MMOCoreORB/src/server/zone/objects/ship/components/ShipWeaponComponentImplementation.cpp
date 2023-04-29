#include "server/zone/objects/ship/components/ShipWeaponComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/DeltaMessage.h"

void ShipWeaponComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<ShipComponentTemplate*>(templateData);

	if (shot != nullptr) {
		const auto& attributeMap = shot->getAttributeMap();

		for (int i = 0; i < attributeMap.size(); ++i) {
			const auto& attribute = attributeMap.elementAt(i).getKey();
			float value = attributeMap.elementAt(i).getValue();

			if (attribute == "maxDamage") {
				maxDamage = value;
			} else if (attribute == "minDamage") {
				minDamage = value;
			} else if (attribute == "shieldEffectiveness") {
				shieldEffectiveness = value;
			} else if (attribute == "armorEffectiveness") {
				armorEffectiveness = value;
			} else if (attribute == "energyPerShot") {
				energyPerShot = value;
			} else if (attribute == "refireRate") {
				refireRate = value;
			}
		}
	}
}

void ShipWeaponComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getTotalExperimentalAttributes(); ++i) {
		const auto& attribute = values->getAttribute(i);
		auto value = values->getCurrentValue(attribute);

		if (attribute == "damage_max" || attribute == "ship_component_weapon_damage_maximum") {
			maxDamage = value;
		} else if (attribute == "damage_min" || attribute == "ship_component_weapon_damage_minimum") {
			minDamage = value;
		} else if (attribute == "effective_shields" || attribute == "ship_component_weapon_effectiveness_shields") {
			shieldEffectiveness = value * 0.001f;
		} else if (attribute == "effective_armor" || attribute == "ship_component_weapon_effectiveness_armor") {
			armorEffectiveness = value * 0.001f;
		} else if (attribute == "energy_per_shot" || attribute == "ship_component_weapon_energy_per_shot") {
			energyPerShot = value;
		} else if (attribute == "refire_rate" || attribute == "ship_component_weapon_refire_rate") {
			refireRate = value * 0.001f;
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

	if (reverseEngineeringLevel != 0) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", reverseEngineeringLevel);
	}
}

void ShipWeaponComponentImplementation::install(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::install(pilot, ship, slot, notifyClient);

	auto deltaVector = notifyClient ? ship->getDeltaVector() : nullptr;
	int command = DeltaMapCommands::ADD;

	ship->setMaxDamage(slot, maxDamage, nullptr, command, deltaVector);
	ship->setMinDamage(slot, minDamage, nullptr, command, deltaVector);
	ship->setShieldEffectiveness(slot, shieldEffectiveness, nullptr, command, deltaVector);
	ship->setArmorEffectiveness(slot, armorEffectiveness, nullptr, command, deltaVector);
	ship->setEnergyPerShot(slot, energyPerShot, nullptr, command, deltaVector);
	ship->setRefireRate(slot, refireRate, nullptr, command, deltaVector);

	ship->setRefireEfficiency(slot, 1.f, nullptr, command, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship, pilot);
	}
}

void ShipWeaponComponentImplementation::uninstall(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);

	auto deltaVector = notifyClient ? ship->getDeltaVector() : nullptr;
	int command = DeltaMapCommands::DROP;

	ship->setMaxDamage(slot, 0.f, nullptr, command, deltaVector);
	ship->setMinDamage(slot, 0.f, nullptr, command, deltaVector);
	ship->setShieldEffectiveness(slot, 0.f, nullptr, command, deltaVector);
	ship->setArmorEffectiveness(slot, 0.f, nullptr, command, deltaVector);
	ship->setEnergyPerShot(slot, 0.f, nullptr, command, deltaVector);
	ship->setRefireRate(slot, 0.f, nullptr, command, deltaVector);

	ship->setRefireEfficiency(slot, 0.f, nullptr, command, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship, pilot);
	}
}
