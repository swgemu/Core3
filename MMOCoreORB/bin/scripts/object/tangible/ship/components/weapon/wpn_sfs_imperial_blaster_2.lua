object_tangible_ship_components_weapon_wpn_sfs_imperial_blaster_2 = object_tangible_ship_components_weapon_shared_wpn_sfs_imperial_blaster_2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_sfs_imperial_blaster_2",

	attributes = {
		{"minDamage", 627.27},
		{"maxDamage", 883.74},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 22.44},
		{"refireRate", 0.34},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 2300},
		{"mass", 2625},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"minDamage", 0.14},
		{"maxDamage", 0.14},
		{"shieldEffectiveness", 0.05},
		{"armorEffectiveness", 0.05},
		{"energyPerShot", 0.17},
		{"refireRate", 0.05},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.17},
		{"mass", 0.17},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_sfs_imperial_blaster_2, "object/tangible/ship/components/weapon/wpn_sfs_imperial_blaster_2.iff")
