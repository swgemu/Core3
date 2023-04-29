object_tangible_ship_components_reactor_rct_corellian_modified_bt3 = object_tangible_ship_components_reactor_shared_rct_corellian_modified_bt3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_corellian_modified_bt3",

	attributes = {
		{"energyGeneration", 28000},
		{"currentHitpoints", 1650.57},
		{"maximumHitpoints", 1650.57},
		{"maximumArmorHitpoints", 825.285},
		{"currentArmorHitpoints", 825.285},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 62040},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"energyGeneration", 0.25},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.32},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_corellian_modified_bt3, "object/tangible/ship/components/reactor/rct_corellian_modified_bt3.iff")
