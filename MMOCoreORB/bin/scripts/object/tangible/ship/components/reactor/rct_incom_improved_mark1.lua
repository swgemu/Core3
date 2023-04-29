object_tangible_ship_components_reactor_rct_incom_improved_mark1 = object_tangible_ship_components_reactor_shared_rct_incom_improved_mark1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_incom_improved_mark1",

	attributes = {
		{"energyGeneration", 10000},
		{"currentHitpoints", 247.5},
		{"maximumHitpoints", 247.5},
		{"maximumArmorHitpoints", 123.75},
		{"currentArmorHitpoints", 123.75},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_incom_improved_mark1, "object/tangible/ship/components/reactor/rct_incom_improved_mark1.iff")
