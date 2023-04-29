object_tangible_ship_components_booster_bst_sap_imperial_1 = object_tangible_ship_components_booster_shared_bst_sap_imperial_1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "bst_sap_imperial_1",

	attributes = {
		{"currentEnergy", 1500},
		{"maximumEnergy", 1500},
		{"rechargeRate", 37.5},
		{"consumptionRate", 150},
		{"acceleration", 30},
		{"maxSpeed", 22.5},
		{"currentHitpoints", 225},
		{"maximumHitpoints", 225},
		{"maximumArmorHitpoints", 112.5},
		{"currentArmorHitpoints", 112.5},
		{"efficiency", 1},
		{"energyMaintenance", 500},
		{"mass", 1400},
		{"reverseEngineeringLevel", 2},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_booster_bst_sap_imperial_1, "object/tangible/ship/components/booster/bst_sap_imperial_1.iff")
