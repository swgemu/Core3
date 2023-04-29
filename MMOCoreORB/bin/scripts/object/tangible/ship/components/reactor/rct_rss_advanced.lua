object_tangible_ship_components_reactor_rct_rss_advanced = object_tangible_ship_components_reactor_shared_rct_rss_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_rss_advanced",

	attributes = {
		{"energyGeneration", 27350},
		{"currentHitpoints", 1155.4},
		{"maximumHitpoints", 1155.4},
		{"maximumArmorHitpoints", 577.7},
		{"currentArmorHitpoints", 577.7},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 51480},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"energyGeneration", 0.177},
		{"maximumArmorHitpoints", 0.06},
		{"energyMaintenance", 0},
		{"mass", 0.28},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_rss_advanced, "object/tangible/ship/components/reactor/rct_rss_advanced.iff")
