object_tangible_ship_components_armor_arm_mission_reward_rebel_incom_ultralight = object_tangible_ship_components_armor_shared_arm_mission_reward_rebel_incom_ultralight:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_mission_reward_rebel_incom_ultralight",

	attributes = {
		{"currentHitpoints", 160},
		{"maximumHitpoints", 160},
		{"maximumArmorHitpoints", 160},
		{"currentArmorHitpoints", 160},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 585},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.0001},
		{"energyMaintenance", 0},
		{"mass", 0.0001},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_mission_reward_rebel_incom_ultralight, "object/tangible/ship/components/armor/arm_mission_reward_rebel_incom_ultralight.iff")
