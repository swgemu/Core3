object_tangible_ship_components_booster_bst_kessel_imperial_cygnus_hyperthrust = object_tangible_ship_components_booster_shared_bst_kessel_imperial_cygnus_hyperthrust:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "bst_kessel_imperial_cygnus_hyperthrust",

	attributes = {
		{"currentEnergy", 1464.1},
		{"maximumEnergy", 1464.1},
		{"rechargeRate", 36.6},
		{"consumptionRate", 146.41},
		{"acceleration", 29.28},
		{"maxSpeed", 22.77},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 600},
		{"mass", 37440},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maximumEnergy", 0.0001},
		{"rechargeRate", 0.0001},
		{"consumptionRate", 0.0001},
		{"acceleration", 0.0001},
		{"maxSpeed", 0.0001},
		{"maximumArmorHitpoints", 0.0001},
		{"energyMaintenance", 0.0001},
		{"mass", 0.0001},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_booster_bst_kessel_imperial_cygnus_hyperthrust, "object/tangible/ship/components/booster/bst_kessel_imperial_cygnus_hyperthrust.iff")
