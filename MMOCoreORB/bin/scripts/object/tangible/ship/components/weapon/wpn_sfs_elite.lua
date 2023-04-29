object_tangible_ship_components_weapon_wpn_sfs_elite = object_tangible_ship_components_weapon_shared_wpn_sfs_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_sfs_elite",

	attributes = {
		{"minDamage", 1783.17},
		{"maxDamage", 2888.5},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 29.868},
		{"refireRate", 0.34},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 2200},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_sfs_elite, "object/tangible/ship/components/weapon/wpn_sfs_elite.iff")
