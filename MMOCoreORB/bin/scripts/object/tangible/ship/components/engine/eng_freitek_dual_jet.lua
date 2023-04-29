object_tangible_ship_components_engine_eng_freitek_dual_jet = object_tangible_ship_components_engine_shared_eng_freitek_dual_jet:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_freitek_dual_jet",

	attributes = {
		{"maxSpeed", 59.01},
		{"maxPitch", 53.6},
		{"maxRoll", 53.6},
		{"maxYaw", 53.6},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 1725},
		{"mass", 16146},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maxSpeed", 0.1},
		{"maxPitch", 0.07},
		{"maxRoll", 0.07},
		{"maxYaw", 0.07},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.14},
		{"mass", 0.14},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_freitek_dual_jet, "object/tangible/ship/components/engine/eng_freitek_dual_jet.iff")
