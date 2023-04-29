object_tangible_ship_components_reactor_rct_moncal_overdriver_s2 = object_tangible_ship_components_reactor_shared_rct_moncal_overdriver_s2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_moncal_overdriver_s2",

	attributes = {
		{"energyGeneration", 21000},
		{"currentHitpoints", 1047.42},
		{"maximumHitpoints", 1047.42},
		{"maximumArmorHitpoints", 523.71},
		{"currentArmorHitpoints", 523.71},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 14421},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"energyGeneration", 0.195},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_moncal_overdriver_s2, "object/tangible/ship/components/reactor/rct_moncal_overdriver_s2.iff")
