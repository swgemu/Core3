object_tangible_ship_components_weapon_wpn_hk_scorcher_elite = object_tangible_ship_components_weapon_shared_wpn_hk_scorcher_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_hk_scorcher_elite",

	attributes = {
		{"minDamage", 1981.3},
		{"maxDamage", 3209.45},
		{"shieldEffectiveness", 0.6},
		{"armorEffectiveness", 0.6},
		{"energyPerShot", 32.357},
		{"refireRate", 0.408},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 2400},
		{"mass", 52650},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"minDamage", 0.12},
		{"maxDamage", 0.12},
		{"shieldEffectiveness", 0.05},
		{"armorEffectiveness", 0.05},
		{"energyPerShot", 0.17},
		{"refireRate", 0.05},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.17},
		{"mass", 0.17},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_hk_scorcher_elite, "object/tangible/ship/components/weapon/wpn_hk_scorcher_elite.iff")
