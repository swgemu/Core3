object_tangible_ship_components_weapon_wpn_kessel_rebel_riiz_combine_slammer_cannon = object_tangible_ship_components_weapon_shared_wpn_kessel_rebel_riiz_combine_slammer_cannon:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_kessel_rebel_riiz_combine_slammer_cannon",

	attributes = {
		{"minDamage", 1981.3},
		{"maxDamage", 3209.45},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 29.868},
		{"refireRate", 0.34},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 2400},
		{"mass", 46800},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_kessel_rebel_riiz_combine_slammer_cannon, "object/tangible/ship/components/weapon/wpn_kessel_rebel_riiz_combine_slammer_cannon.iff")
