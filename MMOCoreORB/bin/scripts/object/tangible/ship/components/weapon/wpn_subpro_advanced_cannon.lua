object_tangible_ship_components_weapon_wpn_subpro_advanced_cannon = object_tangible_ship_components_weapon_shared_wpn_subpro_advanced_cannon:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_subpro_advanced_cannon",

	attributes = {
		{"minDamage", 1074.28},
		{"maxDamage", 1585.58},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 24.684},
		{"refireRate", 0.34},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 2200},
		{"mass", 6875},
		{"reverseEngineeringLevel", 5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_subpro_advanced_cannon, "object/tangible/ship/components/weapon/wpn_subpro_advanced_cannon.iff")
