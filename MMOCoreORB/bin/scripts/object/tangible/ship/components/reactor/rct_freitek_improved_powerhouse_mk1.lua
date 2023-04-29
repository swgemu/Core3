object_tangible_ship_components_reactor_rct_freitek_improved_powerhouse_mk1 = object_tangible_ship_components_reactor_shared_rct_freitek_improved_powerhouse_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_freitek_improved_powerhouse_mk1",

	attributes = {
		{"energyGeneration", 12500},
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
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_freitek_improved_powerhouse_mk1, "object/tangible/ship/components/reactor/rct_freitek_improved_powerhouse_mk1.iff")
