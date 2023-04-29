object_tangible_ship_components_reactor_rct_kessel_rebel_mandal_modified_gorax = object_tangible_ship_components_reactor_shared_rct_kessel_rebel_mandal_modified_gorax:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_kessel_rebel_mandal_modified_gorax",

	attributes = {
		{"energyGeneration", 27500},
		{"currentHitpoints", 1540.53},
		{"maximumHitpoints", 1540.53},
		{"maximumArmorHitpoints", 770.266},
		{"currentArmorHitpoints", 770.266},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 51480},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"energyGeneration", 0.179},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_kessel_rebel_mandal_modified_gorax, "object/tangible/ship/components/reactor/rct_kessel_rebel_mandal_modified_gorax.iff")
