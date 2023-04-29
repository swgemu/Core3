object_tangible_ship_components_reactor_rct_kessel_rebel_incom_overdriven_elite = object_tangible_ship_components_reactor_shared_rct_kessel_rebel_incom_overdriven_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_kessel_rebel_incom_overdriven_elite",

	attributes = {
		{"energyGeneration", 27650},
		{"currentHitpoints", 935.323},
		{"maximumHitpoints", 935.323},
		{"maximumArmorHitpoints", 467.661},
		{"currentArmorHitpoints", 467.661},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 51480},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"energyGeneration", 0.182},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_kessel_rebel_incom_overdriven_elite, "object/tangible/ship/components/reactor/rct_kessel_rebel_incom_overdriven_elite.iff")
