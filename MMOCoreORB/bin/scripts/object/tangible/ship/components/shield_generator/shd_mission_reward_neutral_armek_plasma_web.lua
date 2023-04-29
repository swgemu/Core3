object_tangible_ship_components_shield_generator_shd_mission_reward_neutral_armek_plasma_web = object_tangible_ship_components_shield_generator_shared_shd_mission_reward_neutral_armek_plasma_web:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_mission_reward_neutral_armek_plasma_web",

	attributes = {
		{"shieldRechargeRate", 11.837},
		{"shieldHitpointsMaximumFront", 2433.41},
		{"shieldHitpointsMaximumBack", 2433.41},
		{"currentHitpoints", 1401.65},
		{"maximumHitpoints", 1401.65},
		{"maximumArmorHitpoints", 700.823},
		{"currentArmorHitpoints", 700.823},
		{"efficiency", 1},
		{"energyMaintenance", 2931},
		{"mass", 43543.5},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"shieldRechargeRate", 0.0001},
		{"shieldHitpointsMaximumFront", 0.0001},
		{"shieldHitpointsMaximumBack", 0.0001},
		{"maximumArmorHitpoints", 0.0001},
		{"energyMaintenance", 0.0001},
		{"mass", 0.0001},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_mission_reward_neutral_armek_plasma_web, "object/tangible/ship/components/shield_generator/shd_mission_reward_neutral_armek_plasma_web.iff")
