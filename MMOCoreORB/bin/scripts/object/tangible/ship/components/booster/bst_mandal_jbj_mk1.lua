object_tangible_ship_components_booster_bst_mandal_jbj_mk1 = object_tangible_ship_components_booster_shared_bst_mandal_jbj_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "bst_mandal_jbj_mk1",

	attributes = {
		{"currentEnergy", 1000},
		{"maximumEnergy", 1000},
		{"rechargeRate", 25},
		{"consumptionRate", 100},
		{"acceleration", 20},
		{"maxSpeed", 15},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 500},
		{"mass", 800},
		{"reverseEngineeringLevel", 1},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_booster_bst_mandal_jbj_mk1, "object/tangible/ship/components/booster/bst_mandal_jbj_mk1.iff")
