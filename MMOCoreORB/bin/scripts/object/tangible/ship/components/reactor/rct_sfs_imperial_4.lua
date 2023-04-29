object_tangible_ship_components_reactor_rct_sfs_imperial_4 = object_tangible_ship_components_reactor_shared_rct_sfs_imperial_4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_sfs_imperial_4",

	attributes = {
		{"energyGeneration", 19000},
		{"currentHitpoints", 952.2},
		{"maximumHitpoints", 952.2},
		{"maximumArmorHitpoints", 476.1},
		{"currentArmorHitpoints", 476.1},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 14421},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"energyGeneration", 0.175},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_sfs_imperial_4, "object/tangible/ship/components/reactor/rct_sfs_imperial_4.iff")
