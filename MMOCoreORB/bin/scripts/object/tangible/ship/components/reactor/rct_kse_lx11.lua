object_tangible_ship_components_reactor_rct_kse_lx11 = object_tangible_ship_components_reactor_shared_rct_kse_lx11:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_kse_lx11",

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
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_kse_lx11, "object/tangible/ship/components/reactor/rct_kse_lx11.iff")
