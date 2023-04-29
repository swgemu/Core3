object_tangible_ship_components_reactor_rct_watto_sunray_3 = object_tangible_ship_components_reactor_shared_rct_watto_sunray_3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_watto_sunray_3",

	attributes = {
		{"energyGeneration", 13500},
		{"currentHitpoints", 569.25},
		{"maximumHitpoints", 569.25},
		{"maximumArmorHitpoints", 284.625},
		{"currentArmorHitpoints", 284.625},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 5775},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_watto_sunray_3, "object/tangible/ship/components/reactor/rct_watto_sunray_3.iff")
