object_tangible_ship_components_weapon_capacitor_cap_subpro_defiant_c1 = object_tangible_ship_components_weapon_capacitor_shared_cap_subpro_defiant_c1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_subpro_defiant_c1",

	attributes = {
		{"currentEnergy", 635.25},
		{"maxEnergy", 635.25},
		{"rechargeRate", 25.41},
		{"currentHitpoints", 698.28},
		{"maximumHitpoints", 698.28},
		{"maximumArmorHitpoints", 349.14},
		{"currentArmorHitpoints", 349.14},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 7187.5},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_subpro_defiant_c1, "object/tangible/ship/components/weapon_capacitor/cap_subpro_defiant_c1.iff")
