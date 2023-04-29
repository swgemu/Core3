object_tangible_ship_components_weapon_wpn_sfs_imperial_special_forces_blaster = object_tangible_ship_components_weapon_shared_wpn_sfs_imperial_special_forces_blaster:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_sfs_imperial_special_forces_blaster",

	attributes = {
		{"minDamage", 1989.78},
		{"maxDamage", 3076.66},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 33.945},
		{"refireRate", 0.425},
		{"currentHitpoints", 1284.84},
		{"maximumHitpoints", 1284.84},
		{"maximumArmorHitpoints", 642.42},
		{"currentArmorHitpoints", 642.42},
		{"efficiency", 1},
		{"energyMaintenance", 2300},
		{"mass", 34125},
		{"reverseEngineeringLevel", 8},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_sfs_imperial_special_forces_blaster, "object/tangible/ship/components/weapon/wpn_sfs_imperial_special_forces_blaster.iff")
