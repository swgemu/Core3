object_tangible_ship_components_weapon_wpn_mission_reward_rebel_taim_ion_driver = object_tangible_ship_components_weapon_shared_wpn_mission_reward_rebel_taim_ion_driver:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_mission_reward_rebel_taim_ion_driver",

	attributes = {
		{"minDamage", 913.5},
		{"maxDamage", 1287},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 28.05},
		{"refireRate", 0.425},
		{"currentHitpoints", 517.5},
		{"maximumHitpoints", 517.5},
		{"maximumArmorHitpoints", 258.75},
		{"currentArmorHitpoints", 258.75},
		{"efficiency", 1},
		{"energyMaintenance", 2600},
		{"mass", 5687.5},
		{"reverseEngineeringLevel", 4},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_mission_reward_rebel_taim_ion_driver, "object/tangible/ship/components/weapon/wpn_mission_reward_rebel_taim_ion_driver.iff")
