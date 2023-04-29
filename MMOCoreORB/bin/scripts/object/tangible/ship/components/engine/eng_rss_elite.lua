object_tangible_ship_components_engine_eng_rss_elite = object_tangible_ship_components_engine_shared_eng_rss_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_rss_elite",

	attributes = {
		{"maxSpeed", 82.6125},
		{"maxPitch", 74.5631},
		{"maxRoll", 74.5631},
		{"maxYaw", 74.5631},
		{"currentHitpoints", 1375.47},
		{"maximumHitpoints", 1375.47},
		{"maximumArmorHitpoints", 687.737},
		{"currentArmorHitpoints", 687.737},
		{"efficiency", 1},
		{"energyMaintenance", 1800},
		{"mass", 50760},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maxSpeed", 0.1},
		{"maxPitch", 0.06},
		{"maxRoll", 0.06},
		{"maxYaw", 0.06},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.14},
		{"mass", 0.14},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_rss_elite, "object/tangible/ship/components/engine/eng_rss_elite.iff")
