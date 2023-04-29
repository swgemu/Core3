object_tangible_ship_components_weapon_wpn_rendili_fr13_disruptor = object_tangible_ship_components_weapon_shared_wpn_rendili_fr13_disruptor:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_rendili_fr13_disruptor",

	attributes = {
		{"minDamage", 1074.28},
		{"maxDamage", 1585.58},
		{"shieldEffectiveness", 0.4},
		{"armorEffectiveness", 0.6},
		{"energyPerShot", 24.684},
		{"refireRate", 0.34},
		{"currentHitpoints", 698.28},
		{"maximumHitpoints", 698.28},
		{"maximumArmorHitpoints", 349.14},
		{"currentArmorHitpoints", 349.14},
		{"efficiency", 1},
		{"energyMaintenance", 2200},
		{"mass", 7500},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_rendili_fr13_disruptor, "object/tangible/ship/components/weapon/wpn_rendili_fr13_disruptor.iff")
