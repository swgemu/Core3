#include "server/zone/objects/ship/components/ShipWeaponComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/ship/ShipMissileData.h"
#include "server/zone/objects/ship/ShipCountermeasureData.h"
#include "server/zone/objects/ship/components/ShipMissileComponent.h"
#include "server/zone/objects/ship/components/ShipCounterMeasureComponent.h"

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

	if (getClientGameObjectType() == SceneObjectType::SHIPCOUNTERMEASURELAUNCHER) {
		int ammoType = ShipCountermeasureData::getLauncherAmmoType(componentDataName);
		if (ammoType != -1) {
			ammoClass = ammoType;
		}
	} else if (getClientGameObjectType() == SceneObjectType::SHIPWEAPONLAUNCHER) {
		int ammoType = ShipMissileData::getLauncherAmmoType(componentDataName);
		if (ammoType != -1) {
			ammoClass = ammoType;
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
	ship->setCurrentAmmo(slot, 0, nullptr, command, deltaVector);
	ship->setMaxAmmo(slot, 0, nullptr, command, deltaVector);
	ship->setAmmoClass(slot, ammoClass, nullptr, command, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship);
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
	ship->setCurrentAmmo(slot, 0, nullptr, command, deltaVector);
	ship->setMaxAmmo(slot, 0, nullptr, command, deltaVector);
	ship->setAmmoClass(slot, 0, nullptr, command, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship);
	}
}

void ShipWeaponComponentImplementation::installAmmo(CreatureObject* pilot, ShipObject* ship, Component* ammo, int slot, bool notifyClient) {
	if (pilot == nullptr || ship == nullptr || ammo == nullptr) {
		return;
	}

	auto deltaVector = notifyClient ? ship->getDeltaVector() : nullptr;
	uint8 command = DeltaMapCommands::SET;

	float ammoMin = 0.f;
	float ammoMax = 0.f;
	float ammoShield = 0.f;
	float ammoArmor = 0.f;
	float ammoEnergy = 0.f;
	float ammoRefire = 0.f;
	float ammoCount = ammo->getUseCount();

	if (ammo->getGameObjectType() == SceneObjectType::SHIPCOUNTERMEASURE) {
		auto counter = dynamic_cast<ShipCounterMeasureComponent*>(ammo);

		if (counter != nullptr) {
			ammoMin = counter->getEffectivenessMin();
			ammoMax =  counter->getEffectivenessMax();
			ammoEnergy =  counter->getEnergyPerShot();
			ammoRefire =  counter->getRefireRate();
		}
	} else if (ammo->getGameObjectType() == SceneObjectType::SHIPMISSILE) {
		auto missile = dynamic_cast<ShipMissileComponent*>(ammo);

		if (missile != nullptr) {
			ammoMin = missile->getMinDamage();
			ammoMax =  missile->getMinDamage();
			ammoShield = missile->getShieldEffectiveness();
			ammoArmor = missile->getArmorEffectiveness();
			ammoRefire =  missile->getRefireRate();
		}
	}

	ship->setMinDamage(slot, ammoMin, nullptr, command, deltaVector);
	ship->setMaxDamage(slot, ammoMax, nullptr, command, deltaVector);
	ship->setShieldEffectiveness(slot, ammoShield, nullptr, command, deltaVector);
	ship->setArmorEffectiveness(slot, ammoArmor, nullptr, command, deltaVector);
	ship->setEnergyPerShot(slot, ammoEnergy, nullptr, command, deltaVector);
	ship->setRefireRate(slot, ammoRefire, nullptr, command, deltaVector);
	ship->setRefireEfficiency(slot, 1.f, nullptr, command, deltaVector);
	ship->setCurrentAmmo(slot, ammoCount, nullptr, command, deltaVector);
	ship->setMaxAmmo(slot, ammoCount, nullptr, command, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship);
	}
}

void ShipWeaponComponentImplementation::uninstallAmmo(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	if (pilot == nullptr || ship == nullptr) {
		return;
	}

	auto deltaVector = notifyClient ? ship->getDeltaVector() : nullptr;
	int command = DeltaMapCommands::SET;

	ship->setMaxDamage(slot, maxDamage, nullptr, command, deltaVector);
	ship->setMinDamage(slot, minDamage, nullptr, command, deltaVector);
	ship->setShieldEffectiveness(slot, shieldEffectiveness, nullptr, command, deltaVector);
	ship->setArmorEffectiveness(slot, armorEffectiveness, nullptr, command, deltaVector);
	ship->setEnergyPerShot(slot, energyPerShot, nullptr, command, deltaVector);
	ship->setRefireRate(slot, refireRate, nullptr, command, deltaVector);
	ship->setRefireEfficiency(slot, 0.f, nullptr, command, deltaVector);
	ship->setCurrentAmmo(slot, 0, nullptr, command, deltaVector);
	ship->setMaxAmmo(slot, 0, nullptr, command, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship);
	}
}
