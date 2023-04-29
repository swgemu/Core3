object_tangible_ship_components_weapon_capacitor_cap_subpro_experimental = object_tangible_ship_components_weapon_capacitor_shared_cap_subpro_experimental:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_subpro_experimental",

	attributes = {
		{"currentEnergy", 1317.69},
		{"maxEnergy", 1317.69},
		{"rechargeRate", 43.92},
		{"currentHitpoints", 1650.57},
		{"maximumHitpoints", 1650.57},
		{"maximumArmorHitpoints", 825.285},
		{"currentArmorHitpoints", 825.285},
		{"efficiency", 1},
		{"energyMaintenance", 1400},
		{"mass", 56400},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_subpro_experimental, "object/tangible/ship/components/weapon_capacitor/cap_subpro_experimental.iff")
