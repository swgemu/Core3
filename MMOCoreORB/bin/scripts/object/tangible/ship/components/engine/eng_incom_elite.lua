object_tangible_ship_components_engine_eng_incom_elite = object_tangible_ship_components_engine_shared_eng_incom_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_incom_elite",

	attributes = {
		{"maxSpeed", 82.6125},
		{"maxPitch", 71.0125},
		{"maxRoll", 71.0125},
		{"maxYaw", 71.0125},
		{"currentHitpoints", 1513.02},
		{"maximumHitpoints", 1513.02},
		{"maximumArmorHitpoints", 756.511},
		{"currentArmorHitpoints", 756.511},
		{"efficiency", 1},
		{"energyMaintenance", 1800},
		{"mass", 54990},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_incom_elite, "object/tangible/ship/components/engine/eng_incom_elite.iff")
