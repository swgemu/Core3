object_tangible_ship_components_reactor_rct_taim_experimental_s2 = object_tangible_ship_components_reactor_shared_rct_taim_experimental_s2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_taim_experimental_s2",

	attributes = {
		{"energyGeneration", 26400},
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
		{"energyGeneration", 0.176},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.32},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_taim_experimental_s2, "object/tangible/ship/components/reactor/rct_taim_experimental_s2.iff")
