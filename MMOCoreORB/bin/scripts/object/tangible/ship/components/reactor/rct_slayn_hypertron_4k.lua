object_tangible_ship_components_reactor_rct_slayn_hypertron_4k = object_tangible_ship_components_reactor_shared_rct_slayn_hypertron_4k:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_slayn_hypertron_4k",

	attributes = {
		{"energyGeneration", 32000},
		{"currentHitpoints", 1650.57},
		{"maximumHitpoints", 1650.57},
		{"maximumArmorHitpoints", 825.285},
		{"currentArmorHitpoints", 825.285},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 62040},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"energyGeneration", 0.275},
		{"maximumArmorHitpoints", 0.07},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_slayn_hypertron_4k, "object/tangible/ship/components/reactor/rct_slayn_hypertron_4k.iff")
