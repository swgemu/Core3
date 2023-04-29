object_tangible_ship_components_reactor_rct_mandal_dxr6 = object_tangible_ship_components_reactor_shared_rct_mandal_dxr6:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_mandal_dxr6",

	attributes = {
		{"energyGeneration", 26550},
		{"currentHitpoints", 1471.73},
		{"maximumHitpoints", 1471.73},
		{"maximumArmorHitpoints", 735.864},
		{"currentArmorHitpoints", 735.864},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 36036},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"energyGeneration", 0.176},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_mandal_dxr6, "object/tangible/ship/components/reactor/rct_mandal_dxr6.iff")
