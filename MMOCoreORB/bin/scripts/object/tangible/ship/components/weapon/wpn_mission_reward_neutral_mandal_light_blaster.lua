object_tangible_ship_components_weapon_wpn_mission_reward_neutral_mandal_light_blaster = object_tangible_ship_components_weapon_shared_wpn_mission_reward_neutral_mandal_light_blaster:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_mission_reward_neutral_mandal_light_blaster",

	attributes = {
		{"minDamage", 348},
		{"maxDamage", 468},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 20.4},
		{"refireRate", 0.34},
		{"currentHitpoints", 180},
		{"maximumHitpoints", 180},
		{"maximumArmorHitpoints", 90},
		{"currentArmorHitpoints", 90},
		{"efficiency", 1},
		{"energyMaintenance", 2400},
		{"mass", 1200},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"minDamage", 0.0001},
		{"maxDamage", 0.0001},
		{"shieldEffectiveness", 0.0001},
		{"armorEffectiveness", 0.0001},
		{"energyPerShot", 0.0001},
		{"refireRate", 0.0001},
		{"maximumArmorHitpoints", 0.0001},
		{"energyMaintenance", 0.0001},
		{"mass", 0.0001},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_mission_reward_neutral_mandal_light_blaster, "object/tangible/ship/components/weapon/wpn_mission_reward_neutral_mandal_light_blaster.iff")
