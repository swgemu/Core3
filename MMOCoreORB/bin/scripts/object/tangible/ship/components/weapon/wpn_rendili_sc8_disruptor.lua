object_tangible_ship_components_weapon_wpn_rendili_sc8_disruptor = object_tangible_ship_components_weapon_shared_wpn_rendili_sc8_disruptor:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_rendili_sc8_disruptor",

	attributes = {
		{"minDamage", 1639.57},
		{"maxDamage", 2535.17},
		{"shieldEffectiveness", 0.6},
		{"armorEffectiveness", 0.4},
		{"energyPerShot", 27.156},
		{"refireRate", 0.34},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 2500},
		{"mass", 17940},
		{"reverseEngineeringLevel", 7},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_rendili_sc8_disruptor, "object/tangible/ship/components/weapon/wpn_rendili_sc8_disruptor.iff")
