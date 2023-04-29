object_tangible_ship_components_reactor_rct_subpro_aurora_max = object_tangible_ship_components_reactor_shared_rct_subpro_aurora_max:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_subpro_aurora_max",

	attributes = {
		{"energyGeneration", 25350},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 20592},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"energyGeneration", 0.176},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.32},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_subpro_aurora_max, "object/tangible/ship/components/reactor/rct_subpro_aurora_max.iff")
