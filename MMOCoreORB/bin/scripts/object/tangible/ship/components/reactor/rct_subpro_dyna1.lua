object_tangible_ship_components_reactor_rct_subpro_dyna1 = object_tangible_ship_components_reactor_shared_rct_subpro_dyna1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_subpro_dyna1",

	attributes = {
		{"energyGeneration", 10000},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 1320},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"energyGeneration", 0.21},
		{"maximumArmorHitpoints", 0.06},
		{"energyMaintenance", 0},
		{"mass", 0.31},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_subpro_dyna1, "object/tangible/ship/components/reactor/rct_subpro_dyna1.iff")
