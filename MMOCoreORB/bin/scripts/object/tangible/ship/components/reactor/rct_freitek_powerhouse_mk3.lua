object_tangible_ship_components_reactor_rct_freitek_powerhouse_mk3 = object_tangible_ship_components_reactor_shared_rct_freitek_powerhouse_mk3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_freitek_powerhouse_mk3",

	attributes = {
		{"energyGeneration", 26100},
		{"currentHitpoints", 1541.81},
		{"maximumHitpoints", 1541.81},
		{"maximumArmorHitpoints", 770.905},
		{"currentArmorHitpoints", 770.905},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 36036},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"energyGeneration", 0.176},
		{"maximumArmorHitpoints", 0.06},
		{"energyMaintenance", 0},
		{"mass", 0.31},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_freitek_powerhouse_mk3, "object/tangible/ship/components/reactor/rct_freitek_powerhouse_mk3.iff")
