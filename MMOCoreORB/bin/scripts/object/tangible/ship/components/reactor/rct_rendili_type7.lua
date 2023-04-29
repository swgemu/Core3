object_tangible_ship_components_reactor_rct_rendili_type7 = object_tangible_ship_components_reactor_shared_rct_rendili_type7:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_rendili_type7",

	attributes = {
		{"energyGeneration", 25100},
		{"currentHitpoints", 1027.87},
		{"maximumHitpoints", 1027.87},
		{"maximumArmorHitpoints", 513.937},
		{"currentArmorHitpoints", 513.937},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 20592},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"energyGeneration", 0.176},
		{"maximumArmorHitpoints", 0.06},
		{"energyMaintenance", 0},
		{"mass", 0.31},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_rendili_type7, "object/tangible/ship/components/reactor/rct_rendili_type7.iff")
