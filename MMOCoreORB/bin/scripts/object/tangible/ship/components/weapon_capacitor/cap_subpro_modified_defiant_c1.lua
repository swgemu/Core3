object_tangible_ship_components_weapon_capacitor_cap_subpro_modified_defiant_c1 = object_tangible_ship_components_weapon_capacitor_shared_cap_subpro_modified_defiant_c1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_subpro_modified_defiant_c1",

	attributes = {
		{"currentEnergy", 816.75},
		{"maxEnergy", 816.75},
		{"rechargeRate", 32.67},
		{"currentHitpoints", 952.2},
		{"maximumHitpoints", 952.2},
		{"maximumArmorHitpoints", 476.1},
		{"currentArmorHitpoints", 476.1},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 9832.5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_subpro_modified_defiant_c1, "object/tangible/ship/components/weapon_capacitor/cap_subpro_modified_defiant_c1.iff")
