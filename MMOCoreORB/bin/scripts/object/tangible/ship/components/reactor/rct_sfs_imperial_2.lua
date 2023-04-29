object_tangible_ship_components_reactor_rct_sfs_imperial_2 = object_tangible_ship_components_reactor_shared_rct_sfs_imperial_2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_sfs_imperial_2",

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
		{"energyGeneration", 0.22},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_sfs_imperial_2, "object/tangible/ship/components/reactor/rct_sfs_imperial_2.iff")
