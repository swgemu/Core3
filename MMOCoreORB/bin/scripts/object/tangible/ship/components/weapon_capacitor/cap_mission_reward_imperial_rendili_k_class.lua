object_tangible_ship_components_weapon_capacitor_cap_mission_reward_imperial_rendili_k_class = object_tangible_ship_components_weapon_capacitor_shared_cap_mission_reward_imperial_rendili_k_class:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_mission_reward_imperial_rendili_k_class",

	attributes = {
		{"currentEnergy", 952.875},
		{"maxEnergy", 952.875},
		{"rechargeRate", 38.115},
		{"currentHitpoints", 1047.42},
		{"maximumHitpoints", 1047.42},
		{"maximumArmorHitpoints", 523.71},
		{"currentArmorHitpoints", 523.71},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 9775},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_mission_reward_imperial_rendili_k_class, "object/tangible/ship/components/weapon_capacitor/cap_mission_reward_imperial_rendili_k_class.iff")
