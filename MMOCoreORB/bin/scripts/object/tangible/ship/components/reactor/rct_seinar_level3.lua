object_tangible_ship_components_reactor_rct_seinar_level3 = object_tangible_ship_components_reactor_shared_rct_seinar_level3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_seinar_level3",

	attributes = {
		{"energyGeneration", 16000},
		{"currentHitpoints", 571.32},
		{"maximumHitpoints", 571.32},
		{"maximumArmorHitpoints", 285.66},
		{"currentArmorHitpoints", 285.66},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 8250},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"energyGeneration", 0.175},
		{"maximumArmorHitpoints", 0.07},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_seinar_level3, "object/tangible/ship/components/reactor/rct_seinar_level3.iff")
