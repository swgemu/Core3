object_tangible_ship_components_weapon_wpn_incom_tt8 = object_tangible_ship_components_weapon_shared_wpn_incom_tt8:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_incom_tt8",

	attributes = {
		{"minDamage", 784.087},
		{"maxDamage", 1104.68},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 28.05},
		{"refireRate", 0.425},
		{"currentHitpoints", 517.5},
		{"maximumHitpoints", 517.5},
		{"maximumArmorHitpoints", 258.75},
		{"currentArmorHitpoints", 258.75},
		{"efficiency", 1},
		{"energyMaintenance", 2100},
		{"mass", 5031.25},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"minDamage", 0.11},
		{"maxDamage", 0.11},
		{"shieldEffectiveness", 0.05},
		{"armorEffectiveness", 0.05},
		{"energyPerShot", 0.17},
		{"refireRate", 0.05},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.17},
		{"mass", 0.17},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_incom_tt8, "object/tangible/ship/components/weapon/wpn_incom_tt8.iff")
