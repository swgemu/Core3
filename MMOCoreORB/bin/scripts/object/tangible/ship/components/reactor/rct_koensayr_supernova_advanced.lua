object_tangible_ship_components_reactor_rct_koensayr_supernova_advanced = object_tangible_ship_components_reactor_shared_rct_koensayr_supernova_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_koensayr_supernova_advanced",

	attributes = {
		{"energyGeneration", 25550},
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
		{"mass", 0.29},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_koensayr_supernova_advanced, "object/tangible/ship/components/reactor/rct_koensayr_supernova_advanced.iff")
