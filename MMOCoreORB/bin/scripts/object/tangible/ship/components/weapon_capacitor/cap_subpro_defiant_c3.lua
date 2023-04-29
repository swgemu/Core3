object_tangible_ship_components_weapon_capacitor_cap_subpro_defiant_c3 = object_tangible_ship_components_weapon_capacitor_shared_cap_subpro_defiant_c3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_subpro_defiant_c3",

	attributes = {
		{"currentEnergy", 732.05},
		{"maxEnergy", 732.05},
		{"rechargeRate", 29.282},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 1250},
		{"mass", 17940},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maxEnergy", 0.2},
		{"rechargeRate", 0.1},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_subpro_defiant_c3, "object/tangible/ship/components/weapon_capacitor/cap_subpro_defiant_c3.iff")
