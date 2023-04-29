object_tangible_ship_components_reactor_rct_kse_rct_x = object_tangible_ship_components_reactor_shared_rct_kse_rct_x:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_kse_rct_x",

	attributes = {
		{"energyGeneration", 13000},
		{"currentHitpoints", 517.5},
		{"maximumHitpoints", 517.5},
		{"maximumArmorHitpoints", 258.75},
		{"currentArmorHitpoints", 258.75},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 5775},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.32},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_kse_rct_x, "object/tangible/ship/components/reactor/rct_kse_rct_x.iff")
