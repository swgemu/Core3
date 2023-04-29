object_tangible_ship_components_reactor_rct_unknown_distressed_aluminum = object_tangible_ship_components_reactor_shared_rct_unknown_distressed_aluminum:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_distressed_aluminum",

	attributes = {
		{"energyGeneration", 20500},
		{"currentHitpoints", 952.2},
		{"maximumHitpoints", 952.2},
		{"maximumArmorHitpoints", 476.1},
		{"currentArmorHitpoints", 476.1},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 14421},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"energyGeneration", 0.175},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.32},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_unknown_distressed_aluminum, "object/tangible/ship/components/reactor/rct_unknown_distressed_aluminum.iff")
