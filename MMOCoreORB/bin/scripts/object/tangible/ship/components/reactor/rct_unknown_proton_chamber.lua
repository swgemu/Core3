object_tangible_ship_components_reactor_rct_unknown_proton_chamber = object_tangible_ship_components_reactor_shared_rct_unknown_proton_chamber:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_proton_chamber",

	attributes = {
		{"energyGeneration", 21000},
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
		{"energyGeneration", 0.195},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_unknown_proton_chamber, "object/tangible/ship/components/reactor/rct_unknown_proton_chamber.iff")
