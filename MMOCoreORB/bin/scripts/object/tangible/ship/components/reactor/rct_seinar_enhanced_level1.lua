object_tangible_ship_components_reactor_rct_seinar_enhanced_level1 = object_tangible_ship_components_reactor_shared_rct_seinar_enhanced_level1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_seinar_enhanced_level1",

	attributes = {
		{"energyGeneration", 10000},
		{"currentHitpoints", 202.5},
		{"maximumHitpoints", 202.5},
		{"maximumArmorHitpoints", 101.25},
		{"currentArmorHitpoints", 101.25},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 2310},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.07},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_seinar_enhanced_level1, "object/tangible/ship/components/reactor/rct_seinar_enhanced_level1.iff")
