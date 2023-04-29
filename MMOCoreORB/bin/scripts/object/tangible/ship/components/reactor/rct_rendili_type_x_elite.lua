object_tangible_ship_components_reactor_rct_rendili_type_x_elite = object_tangible_ship_components_reactor_shared_rct_rendili_type_x_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_rendili_type_x_elite",

	attributes = {
		{"energyGeneration", 28000},
		{"currentHitpoints", 1650.57},
		{"maximumHitpoints", 1650.57},
		{"maximumArmorHitpoints", 825.285},
		{"currentArmorHitpoints", 825.285},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 62040},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"energyGeneration", 0.275},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.28},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_rendili_type_x_elite, "object/tangible/ship/components/reactor/rct_rendili_type_x_elite.iff")
