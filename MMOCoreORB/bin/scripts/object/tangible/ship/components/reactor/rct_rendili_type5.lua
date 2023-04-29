object_tangible_ship_components_reactor_rct_rendili_type5 = object_tangible_ship_components_reactor_shared_rct_rendili_type5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_rendili_type5",

	attributes = {
		{"energyGeneration", 15000},
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
		{"energyGeneration", 0.195},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_rendili_type5, "object/tangible/ship/components/reactor/rct_rendili_type5.iff")
