object_tangible_ship_components_weapon_wpn_incom_advanced_blaster = object_tangible_ship_components_weapon_shared_wpn_incom_advanced_blaster:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_incom_advanced_blaster",

	attributes = {
		{"minDamage", 1342.85},
		{"maxDamage", 1981.97},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 30.855},
		{"refireRate", 0.425},
		{"currentHitpoints", 714.15},
		{"maximumHitpoints", 714.15},
		{"maximumArmorHitpoints", 357.075},
		{"currentArmorHitpoints", 357.075},
		{"efficiency", 1},
		{"energyMaintenance", 2200},
		{"mass", 10925},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_incom_advanced_blaster, "object/tangible/ship/components/weapon/wpn_incom_advanced_blaster.iff")
