object_tangible_ship_components_reactor_rct_sorosuub_fusion_reactor_1 = object_tangible_ship_components_reactor_shared_rct_sorosuub_fusion_reactor_1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_sorosuub_fusion_reactor_1",

	attributes = {
		{"energyGeneration", 11000},
		{"currentHitpoints", 379.5},
		{"maximumHitpoints", 379.5},
		{"maximumArmorHitpoints", 189.75},
		{"currentArmorHitpoints", 189.75},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 3300},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.06},
		{"energyMaintenance", 0},
		{"mass", 0.29},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_sorosuub_fusion_reactor_1, "object/tangible/ship/components/reactor/rct_sorosuub_fusion_reactor_1.iff")
