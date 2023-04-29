object_tangible_ship_components_weapon_capacitor_cap_subpro_valiant_z2 = object_tangible_ship_components_weapon_capacitor_shared_cap_subpro_valiant_z2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_subpro_valiant_z2",

	attributes = {
		{"currentEnergy", 522.5},
		{"maxEnergy", 522.5},
		{"rechargeRate", 20.9},
		{"currentHitpoints", 327.75},
		{"maximumHitpoints", 327.75},
		{"maximumArmorHitpoints", 163.875},
		{"currentArmorHitpoints", 163.875},
		{"efficiency", 1},
		{"energyMaintenance", 1000},
		{"mass", 2500},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_subpro_valiant_z2, "object/tangible/ship/components/weapon_capacitor/cap_subpro_valiant_z2.iff")
