object_tangible_ship_components_reactor_rct_freitek_level1 = object_tangible_ship_components_reactor_shared_rct_freitek_level1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_freitek_level1",

	attributes = {
		{"energyGeneration", 10500},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 1320},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_freitek_level1, "object/tangible/ship/components/reactor/rct_freitek_level1.iff")
