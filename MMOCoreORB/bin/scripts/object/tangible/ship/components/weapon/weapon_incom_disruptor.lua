object_tangible_ship_components_weapon_weapon_incom_disruptor = object_tangible_ship_components_weapon_shared_weapon_incom_disruptor:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_incom_disruptor",

	attributes = {
		{"minDamage", 609},
		{"maxDamage", 858},
		{"shieldEffectiveness", 0.3},
		{"armorEffectiveness", 0.7},
		{"energyPerShot", 22.44},
		{"refireRate", 0.34},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 2100},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_weapon_incom_disruptor, "object/tangible/ship/components/weapon/weapon_incom_disruptor.iff")
