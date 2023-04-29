object_tangible_ship_components_weapon_wpn_armek_sw6 = object_tangible_ship_components_weapon_shared_wpn_armek_sw6:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_armek_sw6",

	attributes = {
		{"minDamage", 1342.85},
		{"maxDamage", 1981.97},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 30.855},
		{"refireRate", 0.425},
		{"currentHitpoints", 793.5},
		{"maximumHitpoints", 793.5},
		{"maximumArmorHitpoints", 396.75},
		{"currentArmorHitpoints", 396.75},
		{"efficiency", 1},
		{"energyMaintenance", 2200},
		{"mass", 11580.5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_armek_sw6, "object/tangible/ship/components/weapon/wpn_armek_sw6.iff")
