object_tangible_ship_components_reactor_rct_sfs_imperial_1 = object_tangible_ship_components_reactor_shared_rct_sfs_imperial_1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_sfs_imperial_1",

	attributes = {
		{"energyGeneration", 10500},
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
		{"maximumArmorHitpoints", 0.06},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_sfs_imperial_1, "object/tangible/ship/components/reactor/rct_sfs_imperial_1.iff")
