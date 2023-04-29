object_tangible_ship_components_weapon_wpn_moncal_light_blaster = object_tangible_ship_components_weapon_shared_wpn_moncal_light_blaster:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_moncal_light_blaster",

	attributes = {
		{"minDamage", 362.5},
		{"maxDamage", 487.5},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 25.5},
		{"refireRate", 0.425},
		{"currentHitpoints", 187.5},
		{"maximumHitpoints", 187.5},
		{"maximumArmorHitpoints", 93.75},
		{"currentArmorHitpoints", 93.75},
		{"efficiency", 1},
		{"energyMaintenance", 1920},
		{"mass", 1697.5},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"minDamage", 0.13},
		{"maxDamage", 0.13},
		{"shieldEffectiveness", 0.05},
		{"armorEffectiveness", 0.05},
		{"energyPerShot", 0.17},
		{"refireRate", 0.05},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.17},
		{"mass", 0.18},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_moncal_light_blaster, "object/tangible/ship/components/weapon/wpn_moncal_light_blaster.iff")
