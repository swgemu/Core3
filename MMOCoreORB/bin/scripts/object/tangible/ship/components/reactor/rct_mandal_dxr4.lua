object_tangible_ship_components_reactor_rct_mandal_dxr4 = object_tangible_ship_components_reactor_shared_rct_mandal_dxr4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_mandal_dxr4",

	attributes = {
		{"energyGeneration", 15000},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 8250},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"energyGeneration", 0.185},
		{"maximumArmorHitpoints", 0.06},
		{"energyMaintenance", 0},
		{"mass", 0.31},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_mandal_dxr4, "object/tangible/ship/components/reactor/rct_mandal_dxr4.iff")
