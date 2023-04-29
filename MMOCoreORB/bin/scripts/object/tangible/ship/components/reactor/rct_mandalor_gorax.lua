object_tangible_ship_components_reactor_rct_mandalor_gorax = object_tangible_ship_components_reactor_shared_rct_mandalor_gorax:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_mandalor_gorax",

	attributes = {
		{"energyGeneration", 27300},
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
		{"energyGeneration", 0.177},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_mandalor_gorax, "object/tangible/ship/components/reactor/rct_mandalor_gorax.iff")
