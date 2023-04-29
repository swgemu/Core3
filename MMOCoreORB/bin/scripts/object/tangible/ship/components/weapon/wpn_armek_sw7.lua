object_tangible_ship_components_weapon_wpn_armek_sw7 = object_tangible_ship_components_weapon_shared_wpn_armek_sw7:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_armek_sw7",

	attributes = {
		{"minDamage", 1989.78},
		{"maxDamage", 3076.66},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 33.945},
		{"refireRate", 0.425},
		{"currentHitpoints", 1051.23},
		{"maximumHitpoints", 1051.23},
		{"maximumArmorHitpoints", 525.617},
		{"currentArmorHitpoints", 525.617},
		{"efficiency", 1},
		{"energyMaintenance", 2300},
		{"mass", 28665},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_armek_sw7, "object/tangible/ship/components/weapon/wpn_armek_sw7.iff")
