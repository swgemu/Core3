object_tangible_ship_components_weapon_wpn_incom_shredder = object_tangible_ship_components_weapon_shared_wpn_incom_shredder:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_incom_shredder",

	attributes = {
		{"minDamage", 362.5},
		{"maxDamage", 487.5},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 25.5},
		{"refireRate", 0.425},
		{"currentHitpoints", 206.25},
		{"maximumHitpoints", 206.25},
		{"maximumArmorHitpoints", 103.125},
		{"currentArmorHitpoints", 103.125},
		{"efficiency", 1},
		{"energyMaintenance", 2000},
		{"mass", 1925},
		{"reverseEngineeringLevel", 2},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_incom_shredder, "object/tangible/ship/components/weapon/wpn_incom_shredder.iff")
