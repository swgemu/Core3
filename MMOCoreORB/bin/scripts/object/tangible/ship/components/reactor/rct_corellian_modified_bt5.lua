object_tangible_ship_components_reactor_rct_corellian_modified_bt5 = object_tangible_ship_components_reactor_shared_rct_corellian_modified_bt5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_corellian_modified_bt5",

	attributes = {
		{"energyGeneration", 30000},
		{"currentHitpoints", 1733.1},
		{"maximumHitpoints", 1733.1},
		{"maximumArmorHitpoints", 866.549},
		{"currentArmorHitpoints", 866.549},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 62040},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"energyGeneration", 0.25},
		{"maximumArmorHitpoints", 0.06},
		{"energyMaintenance", 0},
		{"mass", 0.28},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_corellian_modified_bt5, "object/tangible/ship/components/reactor/rct_corellian_modified_bt5.iff")
