object_tangible_ship_components_weapon_wpn_incom_tt13 = object_tangible_ship_components_weapon_shared_wpn_incom_tt13:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_incom_tt13",

	attributes = {
		{"minDamage", 1074.28},
		{"maxDamage", 1585.58},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 24.684},
		{"refireRate", 0.34},
		{"currentHitpoints", 571.32},
		{"maximumHitpoints", 571.32},
		{"maximumArmorHitpoints", 285.66},
		{"currentArmorHitpoints", 285.66},
		{"efficiency", 1},
		{"energyMaintenance", 2200},
		{"mass", 6250},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_incom_tt13, "object/tangible/ship/components/weapon/wpn_incom_tt13.iff")
