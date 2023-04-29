object_tangible_ship_components_reactor_rct_sds_imperial_1 = object_tangible_ship_components_reactor_shared_rct_sds_imperial_1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_sds_imperial_1",

	attributes = {
		{"energyGeneration", 15000},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 8250},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"energyGeneration", 0.175},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_sds_imperial_1, "object/tangible/ship/components/reactor/rct_sds_imperial_1.iff")
