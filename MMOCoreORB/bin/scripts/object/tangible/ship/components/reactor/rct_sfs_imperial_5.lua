object_tangible_ship_components_reactor_rct_sfs_imperial_5 = object_tangible_ship_components_reactor_shared_rct_sfs_imperial_5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_sfs_imperial_5",

	attributes = {
		{"energyGeneration", 26300},
		{"currentHitpoints", 1401.65},
		{"maximumHitpoints", 1401.65},
		{"maximumArmorHitpoints", 700.823},
		{"currentArmorHitpoints", 700.823},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_sfs_imperial_5, "object/tangible/ship/components/reactor/rct_sfs_imperial_5.iff")
