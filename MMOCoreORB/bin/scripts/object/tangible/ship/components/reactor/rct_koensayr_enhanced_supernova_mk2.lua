object_tangible_ship_components_reactor_rct_koensayr_enhanced_supernova_mk2 = object_tangible_ship_components_reactor_shared_rct_koensayr_enhanced_supernova_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_koensayr_enhanced_supernova_mk2",

	attributes = {
		{"energyGeneration", 13000},
		{"currentHitpoints", 465.75},
		{"maximumHitpoints", 465.75},
		{"maximumArmorHitpoints", 232.875},
		{"currentArmorHitpoints", 232.875},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 5775},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"energyGeneration", 0.2},
		{"maximumArmorHitpoints", 0.07},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_koensayr_enhanced_supernova_mk2, "object/tangible/ship/components/reactor/rct_koensayr_enhanced_supernova_mk2.iff")
