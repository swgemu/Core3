object_tangible_ship_components_armor_arm_mission_reward_imperial_sfs_light_military = object_tangible_ship_components_armor_shared_arm_mission_reward_imperial_sfs_light_military:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_mission_reward_imperial_sfs_light_military",

	attributes = {
		{"currentHitpoints", 460},
		{"maximumHitpoints", 460},
		{"maximumArmorHitpoints", 460},
		{"currentArmorHitpoints", 460},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 2047.5},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.0001},
		{"energyMaintenance", 0},
		{"mass", 0.0001},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_mission_reward_imperial_sfs_light_military, "object/tangible/ship/components/armor/arm_mission_reward_imperial_sfs_light_military.iff")
