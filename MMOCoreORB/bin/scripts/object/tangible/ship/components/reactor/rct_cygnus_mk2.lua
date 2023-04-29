object_tangible_ship_components_reactor_rct_cygnus_mk2 = object_tangible_ship_components_reactor_shared_rct_cygnus_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_cygnus_mk2",

	attributes = {
		{"energyGeneration", 11000},
		{"currentHitpoints", 310.5},
		{"maximumHitpoints", 310.5},
		{"maximumArmorHitpoints", 155.25},
		{"currentArmorHitpoints", 155.25},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 3300},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.07},
		{"energyMaintenance", 0},
		{"mass", 0.31},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_cygnus_mk2, "object/tangible/ship/components/reactor/rct_cygnus_mk2.iff")
