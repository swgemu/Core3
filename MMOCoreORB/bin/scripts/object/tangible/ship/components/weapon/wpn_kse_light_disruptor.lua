object_tangible_ship_components_weapon_wpn_kse_light_disruptor = object_tangible_ship_components_weapon_shared_wpn_kse_light_disruptor:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_kse_light_disruptor",

	attributes = {
		{"minDamage", 290},
		{"maxDamage", 390},
		{"shieldEffectiveness", 0.3},
		{"armorEffectiveness", 0.7},
		{"energyPerShot", 20.4},
		{"refireRate", 0.34},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 1940},
		{"mass", 970},
		{"reverseEngineeringLevel", 1},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_kse_light_disruptor, "object/tangible/ship/components/weapon/wpn_kse_light_disruptor.iff")
