object_tangible_ship_components_reactor_rct_slayn_hypertron_2k = object_tangible_ship_components_reactor_shared_rct_slayn_hypertron_2k:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_slayn_hypertron_2k",

	attributes = {
		{"energyGeneration", 16100},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 8250},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"energyGeneration", 0.175},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_slayn_hypertron_2k, "object/tangible/ship/components/reactor/rct_slayn_hypertron_2k.iff")
