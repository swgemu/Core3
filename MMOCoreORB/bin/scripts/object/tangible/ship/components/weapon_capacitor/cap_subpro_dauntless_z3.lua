object_tangible_ship_components_weapon_capacitor_cap_subpro_dauntless_z3 = object_tangible_ship_components_weapon_capacitor_shared_cap_subpro_dauntless_z3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_subpro_dauntless_z3",

	attributes = {
		{"currentEnergy", 998.25},
		{"maxEnergy", 998.25},
		{"rechargeRate", 39.93},
		{"currentHitpoints", 1401.65},
		{"maximumHitpoints", 1401.65},
		{"maximumArmorHitpoints", 700.823},
		{"currentArmorHitpoints", 700.823},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 31395},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"maxEnergy", 0.25},
		{"rechargeRate", 0.25},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.25},
		{"mass", 0.18},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_subpro_dauntless_z3, "object/tangible/ship/components/weapon_capacitor/cap_subpro_dauntless_z3.iff")
