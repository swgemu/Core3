object_tangible_ship_components_reactor_rct_incom_mark3 = object_tangible_ship_components_reactor_shared_rct_incom_mark3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_incom_mark3",

	attributes = {
		{"energyGeneration", 15750},
		{"currentHitpoints", 698.28},
		{"maximumHitpoints", 698.28},
		{"maximumArmorHitpoints", 349.14},
		{"currentArmorHitpoints", 349.14},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 8250},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"energyGeneration", 0.175},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_incom_mark3, "object/tangible/ship/components/reactor/rct_incom_mark3.iff")
