object_tangible_ship_components_engine_eng_rendili_elite = object_tangible_ship_components_engine_shared_eng_rendili_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_rendili_elite",

	attributes = {
		{"maxSpeed", 78.4819},
		{"maxPitch", 67.4619},
		{"maxRoll", 67.4619},
		{"maxYaw", 71.0125},
		{"currentHitpoints", 1306.7},
		{"maximumHitpoints", 1306.7},
		{"maximumArmorHitpoints", 653.351},
		{"currentArmorHitpoints", 653.351},
		{"efficiency", 1},
		{"energyMaintenance", 1725},
		{"mass", 48645},
		{"reverseEngineeringLevel", 10},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_rendili_elite, "object/tangible/ship/components/engine/eng_rendili_elite.iff")
