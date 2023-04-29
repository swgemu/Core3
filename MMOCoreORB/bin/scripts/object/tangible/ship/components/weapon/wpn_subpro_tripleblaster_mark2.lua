object_tangible_ship_components_weapon_wpn_subpro_tripleblaster_mark2 = object_tangible_ship_components_weapon_shared_wpn_subpro_tripleblaster_mark2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_subpro_tripleblaster_mark2",

	attributes = {
		{"minDamage", 1342.85},
		{"maxDamage", 1981.97},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 33.426},
		{"refireRate", 0.408},
		{"currentHitpoints", 793.5},
		{"maximumHitpoints", 793.5},
		{"maximumArmorHitpoints", 396.75},
		{"currentArmorHitpoints", 396.75},
		{"efficiency", 1},
		{"energyMaintenance", 2200},
		{"mass", 13110},
		{"reverseEngineeringLevel", 6},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_subpro_tripleblaster_mark2, "object/tangible/ship/components/weapon/wpn_subpro_tripleblaster_mark2.iff")
