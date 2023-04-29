object_tangible_ship_components_reactor_rct_freitek_performance_level1 = object_tangible_ship_components_reactor_shared_rct_freitek_performance_level1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_freitek_performance_level1",

	attributes = {
		{"energyGeneration", 10000},
		{"currentHitpoints", 225},
		{"maximumHitpoints", 225},
		{"maximumArmorHitpoints", 112.5},
		{"currentArmorHitpoints", 112.5},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 2310},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.32},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_freitek_performance_level1, "object/tangible/ship/components/reactor/rct_freitek_performance_level1.iff")
