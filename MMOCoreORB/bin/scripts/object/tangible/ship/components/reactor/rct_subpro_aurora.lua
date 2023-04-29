object_tangible_ship_components_reactor_rct_subpro_aurora = object_tangible_ship_components_reactor_shared_rct_subpro_aurora:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_subpro_aurora",

	attributes = {
		{"energyGeneration", 20200},
		{"currentHitpoints", 1047.42},
		{"maximumHitpoints", 1047.42},
		{"maximumArmorHitpoints", 523.71},
		{"currentArmorHitpoints", 523.71},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 14421},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"energyGeneration", 0.175},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_subpro_aurora, "object/tangible/ship/components/reactor/rct_subpro_aurora.iff")
