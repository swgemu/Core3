object_tangible_ship_components_weapon_capacitor_cap_corellian_elite = object_tangible_ship_components_weapon_capacitor_shared_cap_corellian_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_corellian_elite",

	attributes = {
		{"currentEnergy", 933.364},
		{"maxEnergy", 933.364},
		{"rechargeRate", 37.332},
		{"currentHitpoints", 1568.04},
		{"maximumHitpoints", 1568.04},
		{"maximumArmorHitpoints", 784.021},
		{"currentArmorHitpoints", 784.021},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 61100},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_corellian_elite, "object/tangible/ship/components/weapon_capacitor/cap_corellian_elite.iff")
