object_tangible_ship_components_reactor_rct_mandal_dxr = object_tangible_ship_components_reactor_shared_rct_mandal_dxr:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_mandal_dxr",

	attributes = {
		{"energyGeneration", 10000},
		{"currentHitpoints", 165},
		{"maximumHitpoints", 165},
		{"maximumArmorHitpoints", 82.5},
		{"currentArmorHitpoints", 82.5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_mandal_dxr, "object/tangible/ship/components/reactor/rct_mandal_dxr.iff")
