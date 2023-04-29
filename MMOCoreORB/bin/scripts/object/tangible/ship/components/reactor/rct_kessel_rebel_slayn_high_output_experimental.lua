object_tangible_ship_components_reactor_rct_kessel_rebel_slayn_high_output_experimental = object_tangible_ship_components_reactor_shared_rct_kessel_rebel_slayn_high_output_experimental:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_kessel_rebel_slayn_high_output_experimental",

	attributes = {
		{"energyGeneration", 28000},
		{"currentHitpoints", 1402.98},
		{"maximumHitpoints", 1402.98},
		{"maximumArmorHitpoints", 701.492},
		{"currentArmorHitpoints", 701.492},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_kessel_rebel_slayn_high_output_experimental, "object/tangible/ship/components/reactor/rct_kessel_rebel_slayn_high_output_experimental.iff")
