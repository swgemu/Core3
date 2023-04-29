object_tangible_ship_components_weapon_wpn_cygnus_destroyer_mk2 = object_tangible_ship_components_weapon_shared_wpn_cygnus_destroyer_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_cygnus_destroyer_mk2",

	attributes = {
		{"minDamage", 609},
		{"maxDamage", 858},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 22.44},
		{"refireRate", 0.34},
		{"currentHitpoints", 379.5},
		{"maximumHitpoints", 379.5},
		{"maximumArmorHitpoints", 189.75},
		{"currentArmorHitpoints", 189.75},
		{"efficiency", 1},
		{"energyMaintenance", 2100},
		{"mass", 2875},
		{"reverseEngineeringLevel", 3},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_cygnus_destroyer_mk2, "object/tangible/ship/components/weapon/wpn_cygnus_destroyer_mk2.iff")
