object_tangible_ship_components_weapon_wpn_rendili_sc3_disruptor = object_tangible_ship_components_weapon_shared_wpn_rendili_sc3_disruptor:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_rendili_sc3_disruptor",

	attributes = {
		{"minDamage", 1342.85},
		{"maxDamage", 1981.97},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 30.855},
		{"refireRate", 0.425},
		{"currentHitpoints", 872.85},
		{"maximumHitpoints", 872.85},
		{"maximumArmorHitpoints", 436.425},
		{"currentArmorHitpoints", 436.425},
		{"efficiency", 1},
		{"energyMaintenance", 2200},
		{"mass", 13110},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_rendili_sc3_disruptor, "object/tangible/ship/components/weapon/wpn_rendili_sc3_disruptor.iff")
