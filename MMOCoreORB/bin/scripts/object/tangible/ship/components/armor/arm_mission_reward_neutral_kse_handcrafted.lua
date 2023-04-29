object_tangible_ship_components_armor_arm_mission_reward_neutral_kse_handcrafted = object_tangible_ship_components_armor_shared_arm_mission_reward_neutral_kse_handcrafted:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_mission_reward_neutral_kse_handcrafted",

	attributes = {
		{"currentHitpoints", 1269.6},
		{"maximumHitpoints", 1269.6},
		{"maximumArmorHitpoints", 1269.6},
		{"currentArmorHitpoints", 1269.6},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 9180},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.0001},
		{"energyMaintenance", 0},
		{"mass", 0.0001},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_mission_reward_neutral_kse_handcrafted, "object/tangible/ship/components/armor/arm_mission_reward_neutral_kse_handcrafted.iff")
