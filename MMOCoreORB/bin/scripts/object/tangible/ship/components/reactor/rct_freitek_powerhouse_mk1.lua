object_tangible_ship_components_reactor_rct_freitek_powerhouse_mk1 = object_tangible_ship_components_reactor_shared_rct_freitek_powerhouse_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_freitek_powerhouse_mk1",

	attributes = {
		{"energyGeneration", 11000},
		{"currentHitpoints", 379.5},
		{"maximumHitpoints", 379.5},
		{"maximumArmorHitpoints", 189.75},
		{"currentArmorHitpoints", 189.75},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 3300},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"energyGeneration", 0.22},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_freitek_powerhouse_mk1, "object/tangible/ship/components/reactor/rct_freitek_powerhouse_mk1.iff")
