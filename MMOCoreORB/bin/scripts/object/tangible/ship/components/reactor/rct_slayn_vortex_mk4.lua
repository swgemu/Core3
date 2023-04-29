object_tangible_ship_components_reactor_rct_slayn_vortex_mk4 = object_tangible_ship_components_reactor_shared_rct_slayn_vortex_mk4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_slayn_vortex_mk4",

	attributes = {
		{"energyGeneration", 26450},
		{"currentHitpoints", 1471.73},
		{"maximumHitpoints", 1471.73},
		{"maximumArmorHitpoints", 735.864},
		{"currentArmorHitpoints", 735.864},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 36036},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"energyGeneration", 0.176},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.29},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_slayn_vortex_mk4, "object/tangible/ship/components/reactor/rct_slayn_vortex_mk4.iff")
