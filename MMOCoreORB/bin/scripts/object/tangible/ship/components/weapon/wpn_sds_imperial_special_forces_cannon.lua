object_tangible_ship_components_weapon_wpn_sds_imperial_special_forces_cannon = object_tangible_ship_components_weapon_shared_wpn_sds_imperial_special_forces_cannon:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_sds_imperial_special_forces_cannon",

	attributes = {
		{"minDamage", 1591.82},
		{"maxDamage", 2461.33},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 27.156},
		{"refireRate", 0.34},
		{"currentHitpoints", 1027.87},
		{"maximumHitpoints", 1027.87},
		{"maximumArmorHitpoints", 513.937},
		{"currentArmorHitpoints", 513.937},
		{"efficiency", 1},
		{"energyMaintenance", 2300},
		{"mass", 19500},
		{"reverseEngineeringLevel", 7},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_sds_imperial_special_forces_cannon, "object/tangible/ship/components/weapon/wpn_sds_imperial_special_forces_cannon.iff")
