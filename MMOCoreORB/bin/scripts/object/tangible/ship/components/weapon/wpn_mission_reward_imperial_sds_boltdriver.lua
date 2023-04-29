object_tangible_ship_components_weapon_wpn_mission_reward_imperial_sds_boltdriver = object_tangible_ship_components_weapon_shared_wpn_mission_reward_imperial_sds_boltdriver:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_mission_reward_imperial_sds_boltdriver",

	attributes = {
		{"minDamage", 1910.18},
		{"maxDamage", 2953.6},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 27.156},
		{"refireRate", 0.34},
		{"currentHitpoints", 1121.32},
		{"maximumHitpoints", 1121.32},
		{"maximumArmorHitpoints", 560.658},
		{"currentArmorHitpoints", 560.658},
		{"efficiency", 1},
		{"energyMaintenance", 2800},
		{"mass", 21840},
		{"reverseEngineeringLevel", 7},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_mission_reward_imperial_sds_boltdriver, "object/tangible/ship/components/weapon/wpn_mission_reward_imperial_sds_boltdriver.iff")
