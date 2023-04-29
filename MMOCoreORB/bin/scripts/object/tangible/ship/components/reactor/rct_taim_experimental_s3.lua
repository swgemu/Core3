object_tangible_ship_components_reactor_rct_taim_experimental_s3 = object_tangible_ship_components_reactor_shared_rct_taim_experimental_s3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_taim_experimental_s3",

	attributes = {
		{"energyGeneration", 25400},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_taim_experimental_s3, "object/tangible/ship/components/reactor/rct_taim_experimental_s3.iff")
