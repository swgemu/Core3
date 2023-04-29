object_tangible_ship_components_weapon_wpn_armek_sw8 = object_tangible_ship_components_weapon_shared_wpn_armek_sw8:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_armek_sw8",

	attributes = {
		{"minDamage", 1432.64},
		{"maxDamage", 2215.2},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 27.156},
		{"refireRate", 0.34},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 2100},
		{"mass", 17940},
		{"reverseEngineeringLevel", 7},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_armek_sw8, "object/tangible/ship/components/weapon/wpn_armek_sw8.iff")
