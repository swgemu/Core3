object_tangible_ship_components_reactor_rct_cygnus_mk1 = object_tangible_ship_components_reactor_shared_rct_cygnus_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_cygnus_mk1",

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
		{"energyGeneration", 0.22},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_cygnus_mk1, "object/tangible/ship/components/reactor/rct_cygnus_mk1.iff")
