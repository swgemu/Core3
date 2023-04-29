object_tangible_ship_components_reactor_rct_subpro_dyna2 = object_tangible_ship_components_reactor_shared_rct_subpro_dyna2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_subpro_dyna2",

	attributes = {
		{"energyGeneration", 26350},
		{"currentHitpoints", 1261.48},
		{"maximumHitpoints", 1261.48},
		{"maximumArmorHitpoints", 630.74},
		{"currentArmorHitpoints", 630.74},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 36036},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"energyGeneration", 0.176},
		{"maximumArmorHitpoints", 0.07},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_subpro_dyna2, "object/tangible/ship/components/reactor/rct_subpro_dyna2.iff")
