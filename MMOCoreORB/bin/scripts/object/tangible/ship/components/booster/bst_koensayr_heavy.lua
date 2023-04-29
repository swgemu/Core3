object_tangible_ship_components_booster_bst_koensayr_heavy = object_tangible_ship_components_booster_shared_bst_koensayr_heavy:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "bst_koensayr_heavy",

	attributes = {
		{"currentEnergy", 1210},
		{"maximumEnergy", 1210},
		{"rechargeRate", 30.25},
		{"consumptionRate", 121},
		{"acceleration", 24.2},
		{"maxSpeed", 18.48},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 550},
		{"mass", 5500},
		{"reverseEngineeringLevel", 5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_booster_bst_koensayr_heavy, "object/tangible/ship/components/booster/bst_koensayr_heavy.iff")
