object_tangible_ship_components_weapon_capacitor_cap_rendili_overseer_j8 = object_tangible_ship_components_weapon_capacitor_shared_cap_rendili_overseer_j8:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_rendili_overseer_j8",

	attributes = {
		{"currentEnergy", 742.5},
		{"maxEnergy", 742.5},
		{"rechargeRate", 29.7},
		{"currentHitpoints", 517.5},
		{"maximumHitpoints", 517.5},
		{"maximumArmorHitpoints", 258.75},
		{"currentArmorHitpoints", 258.75},
		{"efficiency", 1},
		{"energyMaintenance", 1050},
		{"mass", 3718.75},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_rendili_overseer_j8, "object/tangible/ship/components/weapon_capacitor/cap_rendili_overseer_j8.iff")
