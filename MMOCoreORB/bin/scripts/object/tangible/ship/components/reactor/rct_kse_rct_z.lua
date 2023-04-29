object_tangible_ship_components_reactor_rct_kse_rct_z = object_tangible_ship_components_reactor_shared_rct_kse_rct_z:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_kse_rct_z",

	attributes = {
		{"energyGeneration", 26450},
		{"currentHitpoints", 1401.65},
		{"maximumHitpoints", 1401.65},
		{"maximumArmorHitpoints", 700.823},
		{"currentArmorHitpoints", 700.823},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 36036},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"energyGeneration", 0.186},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_kse_rct_z, "object/tangible/ship/components/reactor/rct_kse_rct_z.iff")
