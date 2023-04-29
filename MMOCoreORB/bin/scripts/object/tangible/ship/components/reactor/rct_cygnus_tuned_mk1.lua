object_tangible_ship_components_reactor_rct_cygnus_tuned_mk1 = object_tangible_ship_components_reactor_shared_rct_cygnus_tuned_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_cygnus_tuned_mk1",

	attributes = {
		{"energyGeneration", 10000},
		{"currentHitpoints", 225},
		{"maximumHitpoints", 225},
		{"maximumArmorHitpoints", 112.5},
		{"currentArmorHitpoints", 112.5},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 2310},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_cygnus_tuned_mk1, "object/tangible/ship/components/reactor/rct_cygnus_tuned_mk1.iff")
