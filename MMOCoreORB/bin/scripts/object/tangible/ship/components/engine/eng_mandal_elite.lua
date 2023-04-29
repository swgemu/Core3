object_tangible_ship_components_engine_eng_mandal_elite = object_tangible_ship_components_engine_shared_eng_mandal_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_mandal_elite",

	attributes = {
		{"maxSpeed", 82.6125},
		{"maxPitch", 71.0125},
		{"maxRoll", 71.0125},
		{"maxYaw", 71.0125},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 1500},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_mandal_elite, "object/tangible/ship/components/engine/eng_mandal_elite.iff")
