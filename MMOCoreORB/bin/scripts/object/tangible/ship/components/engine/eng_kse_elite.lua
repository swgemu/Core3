object_tangible_ship_components_engine_eng_kse_elite = object_tangible_ship_components_engine_shared_eng_kse_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_kse_elite",

	attributes = {
		{"maxSpeed", 86.7431},
		{"maxPitch", 74.5631},
		{"maxRoll", 74.5631},
		{"maxYaw", 74.5631},
		{"currentHitpoints", 1444.25},
		{"maximumHitpoints", 1444.25},
		{"maximumArmorHitpoints", 722.124},
		{"currentArmorHitpoints", 722.124},
		{"efficiency", 1},
		{"energyMaintenance", 1875},
		{"mass", 52875},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_kse_elite, "object/tangible/ship/components/engine/eng_kse_elite.iff")
