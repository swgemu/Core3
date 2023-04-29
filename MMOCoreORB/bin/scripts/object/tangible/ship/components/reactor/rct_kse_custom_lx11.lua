object_tangible_ship_components_reactor_rct_kse_custom_lx11 = object_tangible_ship_components_reactor_shared_rct_kse_custom_lx11:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_kse_custom_lx11",

	attributes = {
		{"energyGeneration", 10500},
		{"currentHitpoints", 225},
		{"maximumHitpoints", 225},
		{"maximumArmorHitpoints", 112.5},
		{"currentArmorHitpoints", 112.5},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 2310},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_kse_custom_lx11, "object/tangible/ship/components/reactor/rct_kse_custom_lx11.iff")
