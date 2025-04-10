#ifndef SHIPCOMPONENTATTRIBUTES_H_
#define SHIPCOMPONENTATTRIBUTES_H_

#include "engine/engine.h"

class ShipComponentAttributes {
public:
	static const Vector<String> ATTRIBUTES;
};

const Vector<String> ShipComponentAttributes::ATTRIBUTES = {
	"ship_component_armor", "armorhpmax",
	"ship_component_hitpoints", "hitpointsmax",
	"ship_component_energy_required", "energy_maintenance",
	"ship_component_mass", "mass",
	"ship_component_booster_energy",
	"ship_component_booster_energy_recharge_rate",
	"ship_component_booster_energy_consumption_rate",
	"ship_component_booster_acceleration",
	"ship_component_booster_speed_maximum",
	"ship_component_capacitor_energy",
	"ship_component_capacitor_energy_recharge_rate",
	"ship_component_droidinterface_speed",
	"ship_component_engine_pitch_rate_maximum",
	"ship_component_engine_yaw_rate_maximum",
	"ship_component_engine_roll_rate_maximum",
	"ship_component_engine_speed_maximum",
	"ship_component_reactor_generation_rate",
	"ship_component_shield_hitpoints_front",
	"ship_component_shield_hitpoints_back",
	"ship_component_shield_recharge_rate",
	"ship_component_weapon_damage_minimum", "damage_min",
	"ship_component_weapon_damage_maximum", "damage_max",
	"ship_component_weapon_effectiveness_shields", "effective_shields",
	"ship_component_weapon_effectiveness_armor", "effective_armor",
	"ship_component_weapon_energy_per_shot", "energy_per_shot",
	"ship_component_weapon_refire_rate", "refire_rate"
};

#endif // SHIPCOMPONENTATTRIBUTES_H_
