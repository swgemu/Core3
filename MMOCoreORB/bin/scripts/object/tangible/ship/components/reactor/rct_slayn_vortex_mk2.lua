object_tangible_ship_components_reactor_rct_slayn_vortex_mk2 = object_tangible_ship_components_reactor_shared_rct_slayn_vortex_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_slayn_vortex_mk2",

	attributes = {
		{"energyGeneration", 20000},
		{"currentHitpoints", 856.98},
		{"maximumHitpoints", 856.98},
		{"maximumArmorHitpoints", 428.49},
		{"currentArmorHitpoints", 428.49},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 14421},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"energyGeneration", 0.175},
		{"maximumArmorHitpoints", 0.07},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_slayn_vortex_mk2, "object/tangible/ship/components/reactor/rct_slayn_vortex_mk2.iff")
