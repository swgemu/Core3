object_tangible_ship_components_reactor_rct_cygnus_advanced = object_tangible_ship_components_reactor_shared_rct_cygnus_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_cygnus_advanced",

	attributes = {
		{"energyGeneration", 27450},
		{"currentHitpoints", 990.342},
		{"maximumHitpoints", 990.342},
		{"maximumArmorHitpoints", 495.171},
		{"currentArmorHitpoints", 495.171},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 51480},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"energyGeneration", 0.177},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_cygnus_advanced, "object/tangible/ship/components/reactor/rct_cygnus_advanced.iff")
