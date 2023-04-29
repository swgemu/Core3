object_tangible_ship_components_weapon_wpn_sds_elite = object_tangible_ship_components_weapon_shared_wpn_sds_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_sds_elite",

	attributes = {
		{"minDamage", 1981.3},
		{"maxDamage", 3209.45},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 29.868},
		{"refireRate", 0.34},
		{"currentHitpoints", 1210.42},
		{"maximumHitpoints", 1210.42},
		{"maximumArmorHitpoints", 605.209},
		{"currentArmorHitpoints", 605.209},
		{"efficiency", 1},
		{"energyMaintenance", 2400},
		{"mass", 50700},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_sds_elite, "object/tangible/ship/components/weapon/wpn_sds_elite.iff")
