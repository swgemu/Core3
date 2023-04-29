object_tangible_ship_components_reactor_rct_incom_elite = object_tangible_ship_components_reactor_shared_rct_incom_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_incom_elite",

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
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_incom_elite, "object/tangible/ship/components/reactor/rct_incom_elite.iff")
