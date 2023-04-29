object_tangible_ship_components_weapon_wpn_hk_scorcher = object_tangible_ship_components_weapon_shared_wpn_hk_scorcher:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_hk_scorcher",

	attributes = {
		{"minDamage", 761.25},
		{"maxDamage", 1072.5},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 28.05},
		{"refireRate", 0.425},
		{"currentHitpoints", 474.375},
		{"maximumHitpoints", 474.375},
		{"maximumArmorHitpoints", 237.188},
		{"currentArmorHitpoints", 237.188},
		{"efficiency", 1},
		{"energyMaintenance", 2100},
		{"mass", 5031.25},
		{"reverseEngineeringLevel", 4},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_hk_scorcher, "object/tangible/ship/components/weapon/wpn_hk_scorcher.iff")
