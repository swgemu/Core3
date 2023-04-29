object_tangible_ship_components_reactor_rct_kessel_imperial_sfs_special_forces = object_tangible_ship_components_reactor_shared_rct_kessel_imperial_sfs_special_forces:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_kessel_imperial_sfs_special_forces",

	attributes = {
		{"energyGeneration", 27200},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 51480},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"energyGeneration", 0.16},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_kessel_imperial_sfs_special_forces, "object/tangible/ship/components/reactor/rct_kessel_imperial_sfs_special_forces.iff")
