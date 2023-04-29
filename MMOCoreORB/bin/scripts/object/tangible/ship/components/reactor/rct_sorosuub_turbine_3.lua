object_tangible_ship_components_reactor_rct_sorosuub_turbine_3 = object_tangible_ship_components_reactor_shared_rct_sorosuub_turbine_3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_sorosuub_turbine_3",

	attributes = {
		{"energyGeneration", 25250},
		{"currentHitpoints", 981.151},
		{"maximumHitpoints", 981.151},
		{"maximumArmorHitpoints", 490.576},
		{"currentArmorHitpoints", 490.576},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 20592},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"energyGeneration", 0.176},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_sorosuub_turbine_3, "object/tangible/ship/components/reactor/rct_sorosuub_turbine_3.iff")
