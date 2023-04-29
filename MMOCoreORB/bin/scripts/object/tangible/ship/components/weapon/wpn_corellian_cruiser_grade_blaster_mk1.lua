object_tangible_ship_components_weapon_wpn_corellian_cruiser_grade_blaster_mk1 = object_tangible_ship_components_weapon_shared_wpn_corellian_cruiser_grade_blaster_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_corellian_cruiser_grade_blaster_mk1",

	attributes = {
		{"minDamage", 298.7},
		{"maxDamage", 401.7},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 20.4},
		{"refireRate", 0.34},
		{"currentHitpoints", 180},
		{"maximumHitpoints", 180},
		{"maximumArmorHitpoints", 90},
		{"currentArmorHitpoints", 90},
		{"efficiency", 1},
		{"energyMaintenance", 2000},
		{"mass", 1100},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"minDamage", 0.11},
		{"maxDamage", 0.11},
		{"shieldEffectiveness", 0.05},
		{"armorEffectiveness", 0.05},
		{"energyPerShot", 0.17},
		{"refireRate", 0.05},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.17},
		{"mass", 0.17},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_corellian_cruiser_grade_blaster_mk1, "object/tangible/ship/components/weapon/wpn_corellian_cruiser_grade_blaster_mk1.iff")
