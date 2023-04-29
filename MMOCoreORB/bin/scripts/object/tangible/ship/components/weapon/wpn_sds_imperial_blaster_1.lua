object_tangible_ship_components_weapon_wpn_sds_imperial_blaster_1 = object_tangible_ship_components_weapon_shared_wpn_sds_imperial_blaster_1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_sds_imperial_blaster_1",

	attributes = {
		{"minDamage", 290},
		{"maxDamage", 390},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 20.4},
		{"refireRate", 0.34},
		{"currentHitpoints", 165},
		{"maximumHitpoints", 165},
		{"maximumArmorHitpoints", 82.5},
		{"currentArmorHitpoints", 82.5},
		{"efficiency", 1},
		{"energyMaintenance", 2000},
		{"mass", 1100},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_sds_imperial_blaster_1, "object/tangible/ship/components/weapon/wpn_sds_imperial_blaster_1.iff")
