object_tangible_ship_components_weapon_wpn_mandal_qv5_disruptor = object_tangible_ship_components_weapon_shared_wpn_mandal_qv5_disruptor:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_mandal_qv5_disruptor",

	attributes = {
		{"minDamage", 1106.51},
		{"maxDamage", 1633.15},
		{"shieldEffectiveness", 0.35},
		{"armorEffectiveness", 0.65},
		{"energyPerShot", 24.684},
		{"refireRate", 0.34},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 2400},
		{"mass", 6875},
		{"reverseEngineeringLevel", 5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_mandal_qv5_disruptor, "object/tangible/ship/components/weapon/wpn_mandal_qv5_disruptor.iff")
