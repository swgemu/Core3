object_tangible_ship_components_weapon_wpn_armek_advanced = object_tangible_ship_components_weapon_shared_wpn_armek_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_armek_advanced",

	attributes = {
		{"minDamage", 1981.3},
		{"maxDamage", 3209.45},
		{"shieldEffectiveness", 0.6},
		{"armorEffectiveness", 0.45},
		{"energyPerShot", 29.868},
		{"refireRate", 0.34},
		{"currentHitpoints", 990.342},
		{"maximumHitpoints", 990.342},
		{"maximumArmorHitpoints", 495.171},
		{"currentArmorHitpoints", 495.171},
		{"efficiency", 1},
		{"energyMaintenance", 2400},
		{"mass", 42900},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_armek_advanced, "object/tangible/ship/components/weapon/wpn_armek_advanced.iff")
