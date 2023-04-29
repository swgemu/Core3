object_tangible_ship_components_booster_bst_surronian_accelerator_mk2 = object_tangible_ship_components_booster_shared_bst_surronian_accelerator_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "bst_surronian_accelerator_mk2",

	attributes = {
		{"currentEnergy", 1996.5},
		{"maximumEnergy", 1996.5},
		{"rechargeRate", 49.92},
		{"consumptionRate", 199.65},
		{"acceleration", 39.93},
		{"maxSpeed", 30.765},
		{"currentHitpoints", 1401.65},
		{"maximumHitpoints", 1401.65},
		{"maximumArmorHitpoints", 700.823},
		{"currentArmorHitpoints", 700.823},
		{"efficiency", 1},
		{"energyMaintenance", 575},
		{"mass", 25116},
		{"reverseEngineeringLevel", 8},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_booster_bst_surronian_accelerator_mk2, "object/tangible/ship/components/booster/bst_surronian_accelerator_mk2.iff")
