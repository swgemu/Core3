object_tangible_ship_components_reactor_rct_kessel_imperial_sds_secret_ops = object_tangible_ship_components_reactor_shared_rct_kessel_imperial_sds_secret_ops:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_kessel_imperial_sds_secret_ops",

	attributes = {
		{"energyGeneration", 28000},
		{"currentHitpoints", 2310.8},
		{"maximumHitpoints", 2310.8},
		{"maximumArmorHitpoints", 1155.4},
		{"currentArmorHitpoints", 1155.4},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 62040},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"energyGeneration", 0.225},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_kessel_imperial_sds_secret_ops, "object/tangible/ship/components/reactor/rct_kessel_imperial_sds_secret_ops.iff")
