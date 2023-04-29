object_tangible_ship_components_weapon_wpn_kessel_imperial_sds_experimental_secret_ops = object_tangible_ship_components_weapon_shared_wpn_kessel_imperial_sds_experimental_secret_ops:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_kessel_imperial_sds_experimental_secret_ops",

	attributes = {
		{"minDamage", 2476.62},
		{"maxDamage", 4011.81},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 37.335},
		{"refireRate", 0.425},
		{"currentHitpoints", 1375.47},
		{"maximumHitpoints", 1375.47},
		{"maximumArmorHitpoints", 687.737},
		{"currentArmorHitpoints", 687.737},
		{"efficiency", 1},
		{"energyMaintenance", 2400},
		{"mass", 56400},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_kessel_imperial_sds_experimental_secret_ops, "object/tangible/ship/components/weapon/wpn_kessel_imperial_sds_experimental_secret_ops.iff")
