object_tangible_ship_components_weapon_wpn_corellian_ag2g_quad_laser = object_tangible_ship_components_weapon_shared_wpn_corellian_ag2g_quad_laser:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_corellian_ag2g_quad_laser",

	attributes = {
		{"minDamage", 2228.96},
		{"maxDamage", 3610.63},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 37.335},
		{"refireRate", 0.425},
		{"currentHitpoints", 1375.47},
		{"maximumHitpoints", 1375.47},
		{"maximumArmorHitpoints", 687.737},
		{"currentArmorHitpoints", 687.737},
		{"efficiency", 1},
		{"energyMaintenance", 2200},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_corellian_ag2g_quad_laser, "object/tangible/ship/components/weapon/wpn_corellian_ag2g_quad_laser.iff")
