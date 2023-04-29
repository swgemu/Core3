object_tangible_ship_components_weapon_capacitor_cap_subpro_dauntless_z5 = object_tangible_ship_components_weapon_capacitor_shared_cap_subpro_dauntless_z5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_subpro_dauntless_z5",

	attributes = {
		{"currentEnergy", 732.05},
		{"maxEnergy", 732.05},
		{"rechargeRate", 35.136},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 46800},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.1},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_subpro_dauntless_z5, "object/tangible/ship/components/weapon_capacitor/cap_subpro_dauntless_z5.iff")
