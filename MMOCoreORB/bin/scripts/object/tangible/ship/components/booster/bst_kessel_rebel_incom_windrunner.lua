object_tangible_ship_components_booster_bst_kessel_rebel_incom_windrunner = object_tangible_ship_components_booster_shared_bst_kessel_rebel_incom_windrunner:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "bst_kessel_rebel_incom_windrunner",

	attributes = {
		{"currentEnergy", 2196.15},
		{"maximumEnergy", 2196.15},
		{"rechargeRate", 54.9},
		{"consumptionRate", 219.615},
		{"acceleration", 43.92},
		{"maxSpeed", 34.155},
		{"currentHitpoints", 1650.57},
		{"maximumHitpoints", 1650.57},
		{"maximumArmorHitpoints", 825.285},
		{"currentArmorHitpoints", 825.285},
		{"efficiency", 1},
		{"energyMaintenance", 600},
		{"mass", 45120},
		{"reverseEngineeringLevel", 10},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_booster_bst_kessel_rebel_incom_windrunner, "object/tangible/ship/components/booster/bst_kessel_rebel_incom_windrunner.iff")
