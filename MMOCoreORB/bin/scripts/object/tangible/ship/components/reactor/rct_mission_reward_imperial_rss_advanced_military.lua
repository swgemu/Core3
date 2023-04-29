object_tangible_ship_components_reactor_rct_mission_reward_imperial_rss_advanced_military = object_tangible_ship_components_reactor_shared_rct_mission_reward_imperial_rss_advanced_military:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_mission_reward_imperial_rss_advanced_military",

	attributes = {
		{"energyGeneration", 24500},
		{"currentHitpoints", 1822.14},
		{"maximumHitpoints", 1822.14},
		{"maximumArmorHitpoints", 911.07},
		{"currentArmorHitpoints", 911.07},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 36036},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"energyGeneration", 0.0001},
		{"maximumArmorHitpoints", 0.0001},
		{"energyMaintenance", 0},
		{"mass", 0.0001},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_mission_reward_imperial_rss_advanced_military, "object/tangible/ship/components/reactor/rct_mission_reward_imperial_rss_advanced_military.iff")
