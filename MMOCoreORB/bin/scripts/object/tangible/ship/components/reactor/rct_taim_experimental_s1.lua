object_tangible_ship_components_reactor_rct_taim_experimental_s1 = object_tangible_ship_components_reactor_shared_rct_taim_experimental_s1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_taim_experimental_s1",

	attributes = {
		{"energyGeneration", 21500},
		{"currentHitpoints", 952.2},
		{"maximumHitpoints", 952.2},
		{"maximumArmorHitpoints", 476.1},
		{"currentArmorHitpoints", 476.1},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 14421},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"energyGeneration", 0.175},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_taim_experimental_s1, "object/tangible/ship/components/reactor/rct_taim_experimental_s1.iff")
