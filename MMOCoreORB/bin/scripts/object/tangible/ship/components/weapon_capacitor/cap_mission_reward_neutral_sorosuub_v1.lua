object_tangible_ship_components_weapon_capacitor_cap_mission_reward_neutral_sorosuub_v1 = object_tangible_ship_components_weapon_capacitor_shared_cap_mission_reward_neutral_sorosuub_v1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_mission_reward_neutral_sorosuub_v1",

	attributes = {
		{"currentEnergy", 907.5},
		{"maxEnergy", 907.5},
		{"rechargeRate", 36.3},
		{"currentHitpoints", 952.2},
		{"maximumHitpoints", 952.2},
		{"maximumArmorHitpoints", 476.1},
		{"currentArmorHitpoints", 476.1},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 9350},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maxEnergy", 0.25},
		{"rechargeRate", 0.25},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.25},
		{"mass", 0.18},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_mission_reward_neutral_sorosuub_v1, "object/tangible/ship/components/weapon_capacitor/cap_mission_reward_neutral_sorosuub_v1.iff")
