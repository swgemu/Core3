object_tangible_ship_components_weapon_wpn_mandal_qv3_disruptor = object_tangible_ship_components_weapon_shared_wpn_mandal_qv3_disruptor:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_mandal_qv3_disruptor",

	attributes = {
		{"minDamage", 548.1},
		{"maxDamage", 772.2},
		{"shieldEffectiveness", 0.4},
		{"armorEffectiveness", 0.6},
		{"energyPerShot", 22.44},
		{"refireRate", 0.34},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 1900},
		{"mass", 2625},
		{"reverseEngineeringLevel", 3},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_mandal_qv3_disruptor, "object/tangible/ship/components/weapon/wpn_mandal_qv3_disruptor.iff")
