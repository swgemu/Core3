object_tangible_ship_components_engine_eng_mission_reward_neutral_mandal_inferno = object_tangible_ship_components_engine_shared_eng_mission_reward_neutral_mandal_inferno:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_mission_reward_neutral_mandal_inferno",

	attributes = {
		{"maxSpeed", 79.02},
		{"maxPitch", 63.2},
		{"maxRoll", 63.2},
		{"maxYaw", 63.2},
		{"currentHitpoints", 1110.9},
		{"maximumHitpoints", 1110.9},
		{"maximumArmorHitpoints", 555.45},
		{"currentArmorHitpoints", 555.45},
		{"efficiency", 1},
		{"energyMaintenance", 2100},
		{"mass", 13765.5},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maxSpeed", 0.0001},
		{"maxPitch", 0.0001},
		{"maxRoll", 0.0001},
		{"maxYaw", 0.0001},
		{"maximumArmorHitpoints", 0.0001},
		{"energyMaintenance", 0.0001},
		{"mass", 0.0001},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_mission_reward_neutral_mandal_inferno, "object/tangible/ship/components/engine/eng_mission_reward_neutral_mandal_inferno.iff")
