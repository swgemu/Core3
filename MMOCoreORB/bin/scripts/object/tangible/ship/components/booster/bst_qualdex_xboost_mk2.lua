object_tangible_ship_components_booster_bst_qualdex_xboost_mk2 = object_tangible_ship_components_booster_shared_bst_qualdex_xboost_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "bst_qualdex_xboost_mk2",

	attributes = {
		{"currentEnergy", 1650},
		{"maximumEnergy", 1650},
		{"rechargeRate", 41.25},
		{"consumptionRate", 165},
		{"acceleration", 33},
		{"maxSpeed", 24.975},
		{"currentHitpoints", 517.5},
		{"maximumHitpoints", 517.5},
		{"maximumArmorHitpoints", 258.75},
		{"currentArmorHitpoints", 258.75},
		{"efficiency", 1},
		{"energyMaintenance", 525},
		{"mass", 3675},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maximumEnergy", 0.1},
		{"rechargeRate", 0.1},
		{"consumptionRate", 0.1},
		{"acceleration", 0.04},
		{"maxSpeed", 0.03},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.15},
		{"mass", 0.15},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_booster_bst_qualdex_xboost_mk2, "object/tangible/ship/components/booster/bst_qualdex_xboost_mk2.iff")
