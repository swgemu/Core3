object_tangible_ship_components_reactor_rct_mandal_dxr5 = object_tangible_ship_components_reactor_shared_rct_mandal_dxr5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_mandal_dxr5",

	attributes = {
		{"energyGeneration", 25000},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 20592},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"energyGeneration", 0.176},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_mandal_dxr5, "object/tangible/ship/components/reactor/rct_mandal_dxr5.iff")
