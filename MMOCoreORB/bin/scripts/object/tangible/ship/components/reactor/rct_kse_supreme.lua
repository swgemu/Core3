object_tangible_ship_components_reactor_rct_kse_supreme = object_tangible_ship_components_reactor_shared_rct_kse_supreme:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_kse_supreme",

	attributes = {
		{"energyGeneration", 27500},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 51480},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"energyGeneration", 0.17},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_kse_supreme, "object/tangible/ship/components/reactor/rct_kse_supreme.iff")
