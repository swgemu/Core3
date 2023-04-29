object_tangible_ship_components_reactor_rct_moncal_overdriver_s1 = object_tangible_ship_components_reactor_shared_rct_moncal_overdriver_s1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_moncal_overdriver_s1",

	attributes = {
		{"energyGeneration", 32000},
		{"currentHitpoints", 1485.51},
		{"maximumHitpoints", 1485.51},
		{"maximumArmorHitpoints", 742.756},
		{"currentArmorHitpoints", 742.756},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 62040},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"energyGeneration", 0.25},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_moncal_overdriver_s1, "object/tangible/ship/components/reactor/rct_moncal_overdriver_s1.iff")
