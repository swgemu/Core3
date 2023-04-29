object_tangible_ship_components_reactor_rct_incom_mark4 = object_tangible_ship_components_reactor_shared_rct_incom_mark4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_incom_mark4",

	attributes = {
		{"energyGeneration", 25500},
		{"currentHitpoints", 840.987},
		{"maximumHitpoints", 840.987},
		{"maximumArmorHitpoints", 420.493},
		{"currentArmorHitpoints", 420.493},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 20592},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"energyGeneration", 0.176},
		{"maximumArmorHitpoints", 0.07},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_incom_mark4, "object/tangible/ship/components/reactor/rct_incom_mark4.iff")
