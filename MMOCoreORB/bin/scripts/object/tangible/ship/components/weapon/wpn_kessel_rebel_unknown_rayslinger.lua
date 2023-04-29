object_tangible_ship_components_weapon_wpn_kessel_rebel_unknown_rayslinger = object_tangible_ship_components_weapon_shared_wpn_kessel_rebel_unknown_rayslinger:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_kessel_rebel_unknown_rayslinger",

	attributes = {
		{"minDamage", 2550.92},
		{"maxDamage", 4132.17},
		{"shieldEffectiveness", 0.75},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 37.335},
		{"refireRate", 0.425},
		{"currentHitpoints", 1375.47},
		{"maximumHitpoints", 1375.47},
		{"maximumArmorHitpoints", 687.737},
		{"currentArmorHitpoints", 687.737},
		{"efficiency", 1},
		{"energyMaintenance", 2600},
		{"mass", 56400},
		{"reverseEngineeringLevel", 10},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_kessel_rebel_unknown_rayslinger, "object/tangible/ship/components/weapon/wpn_kessel_rebel_unknown_rayslinger.iff")
