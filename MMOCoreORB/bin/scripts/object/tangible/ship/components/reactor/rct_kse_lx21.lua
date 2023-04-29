object_tangible_ship_components_reactor_rct_kse_lx21 = object_tangible_ship_components_reactor_shared_rct_kse_lx21:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_kse_lx21",

	attributes = {
		{"energyGeneration", 11500},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 3300},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_kse_lx21, "object/tangible/ship/components/reactor/rct_kse_lx21.iff")
