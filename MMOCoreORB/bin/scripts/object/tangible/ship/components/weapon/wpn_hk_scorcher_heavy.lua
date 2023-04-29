object_tangible_ship_components_weapon_wpn_hk_scorcher_heavy = object_tangible_ship_components_weapon_shared_wpn_hk_scorcher_heavy:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_hk_scorcher_heavy",

	attributes = {
		{"minDamage", 1591.82},
		{"maxDamage", 2461.33},
		{"shieldEffectiveness", 0.6},
		{"armorEffectiveness", 0.6},
		{"energyPerShot", 29.419},
		{"refireRate", 0.408},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 2300},
		{"mass", 20280},
		{"reverseEngineeringLevel", 7},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_hk_scorcher_heavy, "object/tangible/ship/components/weapon/wpn_hk_scorcher_heavy.iff")
