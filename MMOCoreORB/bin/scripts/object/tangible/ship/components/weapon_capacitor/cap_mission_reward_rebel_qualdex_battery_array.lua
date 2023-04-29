object_tangible_ship_components_weapon_capacitor_cap_mission_reward_rebel_qualdex_battery_array = object_tangible_ship_components_weapon_capacitor_shared_cap_mission_reward_rebel_qualdex_battery_array:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_mission_reward_rebel_qualdex_battery_array",

	attributes = {
		{"currentEnergy", 771.375},
		{"maxEnergy", 771.375},
		{"rechargeRate", 30.855},
		{"currentHitpoints", 904.59},
		{"maximumHitpoints", 904.59},
		{"maximumArmorHitpoints", 452.295},
		{"currentArmorHitpoints", 452.295},
		{"efficiency", 1},
		{"energyMaintenance", 1050},
		{"mass", 8925},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_mission_reward_rebel_qualdex_battery_array, "object/tangible/ship/components/weapon_capacitor/cap_mission_reward_rebel_qualdex_battery_array.iff")
