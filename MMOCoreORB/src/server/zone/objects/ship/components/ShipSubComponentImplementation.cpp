#include "server/zone/objects/ship/components/ShipSubComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/DeltaMessage.h"

void ShipSubComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<ShipComponentTemplate*>(templateData);

	if (shot != nullptr) {
		const auto& attributeMap = shot->getAttributeMap();

		for (int i = 0; i < attributeMap.size(); ++i) {
			const auto& attribute = attributeMap.elementAt(i).getKey();
			float value = attributeMap.elementAt(i).getValue();

			if (attribute == "maximumHitpoints") {
				hitpointsMax = value;
			} else if (attribute == "maximumArmorHitpoints") {
				armorMax = value;
			} else if (attribute == "energyMaintenance") {
				energyCost = value;
			} else if (attribute == "mass") {
				mass = value;
			} else if (attribute == "consumptionRate") {
				boosterConsumptionRate = value;
			} else if(attribute == "acceleration") {
				boosterAcceleration = value;
			} else if (attribute == "maximumEnergy") {
				boosterEnergy = value;
			} else if (attribute == "rechargeRate") {
				boosterRechargeRate = value;
			} else if (attribute == "maxSpeed") {
				boosterSpeed = value;
			} else 	if (attribute == "maxEnergy") {
				capacitorEnergy = value;
			} else if (attribute == "rechargeRate") {
				capacitorRechargeRate = value;
			} else if (attribute == "commandSpeed") {
				droidCommandSpeed = value;
			} else 	if (attribute == "energyGeneration") {
				reactorGenerationRate = value;
			} else 	if (attribute == "shieldHitpointsMaximumBack") {
				rearHitpoints = value;
			} else if(attribute == "shieldHitpointsMaximumFront") {
				frontHitpoints = value;
			} else if (attribute == "shieldRechargeRate") {
				rechargeRate = value;
			} else 	if (attribute == "damage_max" || attribute == "ship_component_weapon_damage_maximum") {
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
			} else if (attribute == "maxSpeed") {
				engineSpeedMaximum = value;
			}

		}

	}

}

void ShipSubComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
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
		} else if (attribute == "ship_component_capacitor_energy") {
			capacitorEnergy = value;
		} else if (attribute == "ship_component_capacitor_energy_recharge_rate") {
			capacitorRechargeRate = value;
		} else 	if (attribute == "energy_maintenance" || attribute == "ship_component_energy_required") {
			energyCost = value;
		} else if (attribute == "armorhpmax" || attribute == "ship_component_armor") {
			armorMax = value;
		} else if (attribute == "hitpointsmax" || attribute == "ship_component_hitpoints") {
			hitpointsMax = value;
		} else if (attribute == "mass" || attribute == "ship_component_mass") {
			mass = value;
		} else if (attribute == "ship_component_droidinterface_speed") {
			droidCommandSpeed = value;
		} else 	if (values->hasExperimentalAttribute("ship_component_reactor_generation_rate")) {
			reactorGenerationRate = values->getCurrentValue("ship_component_reactor_generation_rate");
		} else 	if (attribute == "ship_component_shield_hitpoints_back") {
			rearHitpoints = value;
		} else if(attribute == "ship_component_shield_hitpoints_front") {
			frontHitpoints = value;
		} else if (attribute == "ship_component_shield_recharge_rate") {
			rechargeRate = value;
		} else 	if (attribute == "damage_max" || attribute == "ship_component_weapon_damage_maximum") {
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
		} else if (attribute == "ship_component_engine_speed_maximum") {
			engineSpeedMaximum = value;
		}
	}

}

void ShipSubComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	alm->insertAttribute("@obj_attr_n:volume", volume);

	if (!craftersName.isEmpty()) {
		alm->insertAttribute("crafter", craftersName);
	}

	if (!objectSerial.isEmpty()) {
		alm->insertAttribute("serial_number", objectSerial);
	}

	switch (getGameObjectType()) {
		case SceneObjectType::SHIPARMORSUBCOMPONENT:

			alm->insertAttribute("@obj_attr_n:ship_component.ship_component_armor", String::valueOf(Math::getPrecision(armorMax, 1)));
			alm->insertAttribute("@obj_attr_n:ship_component.ship_component_hitpoints", String::valueOf(Math::getPrecision(hitpointsMax, 1)));
			alm->insertAttribute("@obj_attr_n:ship_component.ship_component_mass", String::valueOf(Math::getPrecision(mass, 1)));

			break;

		case SceneObjectType::SHIPBOOSTERSUBCOMPONENT:
			if (boosterEnergy != 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_energy", String::valueOf(Math::getPrecision(boosterEnergy, 1)));
			}
			if (boosterRechargeRate != 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_energy_recharge_rate", String::valueOf(Math::getPrecision(boosterRechargeRate, 1)));
			}
			if (boosterConsumptionRate != 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_energy_consumption_rate", String::valueOf(Math::getPrecision(boosterConsumptionRate, 1)));
			}
			if (boosterAcceleration > 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_acceleration", String::valueOf(Math::getPrecision(boosterAcceleration, 1)));
			}
			if (boosterSpeed > 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_booster_speed_maximum", String::valueOf(Math::getPrecision(boosterSpeed, 1)));
			}
			if (mass > 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_mass", String::valueOf(Math::getPrecision(mass, 1)));
			}
			break;

		case SceneObjectType::SHIPCAPACITORSUBCOMPONENT:

			alm->insertAttribute("@obj_attr_n:ship_component.ship_component_capacitor_energy", String::valueOf(Math::getPrecision(capacitorEnergy, 1)));

			if (energyCost != 0) {
				alm->insertAttribute("@obj_attr_n:ship_component.energy_maintenance",String::valueOf(Math::getPrecision(energyCost, 1)));
			}

			if (capacitorRechargeRate != 0) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_capacitor_energy_recharge_rate", String::valueOf(Math::getPrecision(capacitorRechargeRate, 1)));
			}
			break;

		case SceneObjectType::SHIPDROIDINTERFACESUBCOMPONENT:

			alm->insertAttribute("@obj_attr_n:ship_component.ship_component_droidinterface_speed", droidCommandSpeed);
			alm->insertAttribute("@obj_attr_n:ship_component.energy_maintenance", String::valueOf(Math::getPrecision(energyCost, 1)));
			break;

		case SceneObjectType::SHIPENGINESUBCOMPONENT:

			alm->insertAttribute("@obj_attr_n:ship_component.ship_component_engine_speed_maximum", String::valueOf(Math::getPrecision(engineSpeedMaximum, 1)));
			alm->insertAttribute("@obj_attr_n:ship_component.energy_maintenance", String::valueOf(Math::getPrecision(energyCost, 1)));
			break;

		case SceneObjectType::SHIPREACTORSUBCOMPONENT:

			alm->insertAttribute("@obj_attr_n:ship_component.ship_component_reactor_generation_rate", String::valueOf(Math::getPrecision(reactorGenerationRate, 1)));
			alm->insertAttribute("@obj_attr_n:ship_component.ship_component_mass", String::valueOf(Math::getPrecision(mass, 1)));
			break;

		case SceneObjectType::SHIPSHIELDSUBCOMPONENT:

			if (energyCost != 0) {
				alm->insertAttribute("@obj_attr_n:ship_component.energy_maintenance",String::valueOf(Math::getPrecision(energyCost, 1)));
			}

			if (rearHitpoints != 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_shield_hitpoints_back", String::valueOf(Math::getPrecision(rearHitpoints, 1)));
			}

			if (frontHitpoints != 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_shield_hitpoints_front", String::valueOf(Math::getPrecision(frontHitpoints, 1)));
			}

			if (rechargeRate != 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_shield_recharge_rate", String::valueOf(Math::getPrecision(rechargeRate, 1)));
			}
			break;

		case SceneObjectType::SHIPWEAPONSUBCOMPONENT:

			if (maxDamage != 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.maxdamage", String::valueOf(Math::getPrecision(maxDamage, 3)));
			}

			if (minDamage != 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.mindamage", String::valueOf(Math::getPrecision(minDamage, 3)));
			}

			if (armorEffectiveness != 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_weapon_effectiveness_armor", String::valueOf(Math::getPrecision(armorEffectiveness, 3)));
			}

			if (shieldEffectiveness != 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_weapon_effectiveness_shields", String::valueOf(Math::getPrecision(shieldEffectiveness, 3)));
			}

			if (energyPerShot != 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_weapon_energy_per_shot", String::valueOf(Math::getPrecision(energyPerShot, 1)));
			}

			if (refireRate != 0.f) {
				alm->insertAttribute("@obj_attr_n:ship_component.ship_component_weapon_refire_rate", String::valueOf(Math::getPrecision(refireRate, 3)));
			}
			break;

		default:
			break;
	}
}