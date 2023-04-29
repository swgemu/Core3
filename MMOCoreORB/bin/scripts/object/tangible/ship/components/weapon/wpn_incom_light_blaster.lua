object_tangible_ship_components_weapon_wpn_incom_light_blaster = object_tangible_ship_components_weapon_shared_wpn_incom_light_blaster:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_incom_light_blaster",

	attributes = {
		{"minDamage", 290},
		{"maxDamage", 390},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 20.4},
		{"refireRate", 0.34},
		{"currentHitpoints", 135},
		{"maximumHitpoints", 135},
		{"maximumArmorHitpoints", 67.5},
		{"currentArmorHitpoints", 67.5},
		{"efficiency", 1},
		{"energyMaintenance", 2000},
		{"mass", 900},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_incom_light_blaster, "object/tangible/ship/components/weapon/wpn_incom_light_blaster.iff")
