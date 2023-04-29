object_tangible_ship_components_reactor_rct_kessel_imperial_kdy_powermaster = object_tangible_ship_components_reactor_shared_rct_kessel_imperial_kdy_powermaster:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_kessel_imperial_kdy_powermaster",

	attributes = {
		{"energyGeneration", 27250},
		{"currentHitpoints", 1320.46},
		{"maximumHitpoints", 1320.46},
		{"maximumArmorHitpoints", 660.228},
		{"currentArmorHitpoints", 660.228},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 51480},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"energyGeneration", 0.177},
		{"maximumArmorHitpoints", 0.15},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_kessel_imperial_kdy_powermaster, "object/tangible/ship/components/reactor/rct_kessel_imperial_kdy_powermaster.iff")
