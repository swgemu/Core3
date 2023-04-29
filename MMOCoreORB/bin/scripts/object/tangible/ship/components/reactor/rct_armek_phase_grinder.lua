object_tangible_ship_components_reactor_rct_armek_phase_grinder = object_tangible_ship_components_reactor_shared_rct_armek_phase_grinder:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_armek_phase_grinder",

	attributes = {
		{"energyGeneration", 30000},
		{"currentHitpoints", 1485.51},
		{"maximumHitpoints", 1485.51},
		{"maximumArmorHitpoints", 742.756},
		{"currentArmorHitpoints", 742.756},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 62040},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"energyGeneration", 0.225},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_armek_phase_grinder, "object/tangible/ship/components/reactor/rct_armek_phase_grinder.iff")
