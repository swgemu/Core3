object_tangible_ship_components_booster_bst_kse_bti1 = object_tangible_ship_components_booster_shared_bst_kse_bti1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "bst_kse_bti1",

	attributes = {
		{"currentEnergy", 1100},
		{"maximumEnergy", 1100},
		{"rechargeRate", 27.5},
		{"consumptionRate", 110},
		{"acceleration", 22},
		{"maxSpeed", 16.65},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 525},
		{"mass", 2100},
		{"reverseEngineeringLevel", 3},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_booster_bst_kse_bti1, "object/tangible/ship/components/booster/bst_kse_bti1.iff")
