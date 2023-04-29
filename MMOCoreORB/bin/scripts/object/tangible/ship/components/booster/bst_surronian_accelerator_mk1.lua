object_tangible_ship_components_booster_bst_surronian_accelerator_mk1 = object_tangible_ship_components_booster_shared_bst_surronian_accelerator_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "bst_surronian_accelerator_mk1",

	attributes = {
		{"currentEnergy", 1815},
		{"maximumEnergy", 1815},
		{"rechargeRate", 45.375},
		{"consumptionRate", 181.5},
		{"acceleration", 36.3},
		{"maxSpeed", 27.72},
		{"currentHitpoints", 952.2},
		{"maximumHitpoints", 952.2},
		{"maximumArmorHitpoints", 476.1},
		{"currentArmorHitpoints", 476.1},
		{"efficiency", 1},
		{"energyMaintenance", 550},
		{"mass", 9614},
		{"reverseEngineeringLevel", 6},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_booster_bst_surronian_accelerator_mk1, "object/tangible/ship/components/booster/bst_surronian_accelerator_mk1.iff")
