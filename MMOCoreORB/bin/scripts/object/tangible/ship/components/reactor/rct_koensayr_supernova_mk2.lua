object_tangible_ship_components_reactor_rct_koensayr_supernova_mk2 = object_tangible_ship_components_reactor_shared_rct_koensayr_supernova_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_koensayr_supernova_mk2",

	attributes = {
		{"energyGeneration", 11000},
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
		{"mass", 0.32},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_koensayr_supernova_mk2, "object/tangible/ship/components/reactor/rct_koensayr_supernova_mk2.iff")
