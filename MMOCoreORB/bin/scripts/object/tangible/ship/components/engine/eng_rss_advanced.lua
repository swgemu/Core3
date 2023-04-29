object_tangible_ship_components_engine_eng_rss_advanced = object_tangible_ship_components_engine_shared_eng_rss_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_rss_advanced",

	attributes = {
		{"maxSpeed", 56.1765},
		{"maxPitch", 56.81},
		{"maxRoll", 56.81},
		{"maxYaw", 56.81},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 1800},
		{"mass", 36855},
		{"reverseEngineeringLevel", 9},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_rss_advanced, "object/tangible/ship/components/engine/eng_rss_advanced.iff")
