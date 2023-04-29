object_tangible_ship_components_weapon_wpn_hk_modified_scorcher_elite = object_tangible_ship_components_weapon_shared_wpn_hk_modified_scorcher_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_hk_modified_scorcher_elite",

	attributes = {
		{"minDamage", 2476.62},
		{"maxDamage", 4011.81},
		{"shieldEffectiveness", 0.75},
		{"armorEffectiveness", 0.75},
		{"energyPerShot", 43.557},
		{"refireRate", 0.44625},
		{"currentHitpoints", 1513.02},
		{"maximumHitpoints", 1513.02},
		{"maximumArmorHitpoints", 756.511},
		{"currentArmorHitpoints", 756.511},
		{"efficiency", 1},
		{"energyMaintenance", 2400},
		{"mass", 65800},
		{"reverseEngineeringLevel", 10},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_hk_modified_scorcher_elite, "object/tangible/ship/components/weapon/wpn_hk_modified_scorcher_elite.iff")
