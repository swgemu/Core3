object_tangible_ship_components_weapon_wpn_sds_heavy_imperial_spc_forces_cannon = object_tangible_ship_components_weapon_shared_wpn_sds_heavy_imperial_spc_forces_cannon:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_sds_heavy_imperial_spc_forces_cannon",

	attributes = {
		{"minDamage", 1989.78},
		{"maxDamage", 3076.66},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 35.076},
		{"refireRate", 0.408},
		{"currentHitpoints", 1401.65},
		{"maximumHitpoints", 1401.65},
		{"maximumArmorHitpoints", 700.823},
		{"currentArmorHitpoints", 700.823},
		{"efficiency", 1},
		{"energyMaintenance", 2300},
		{"mass", 35490},
		{"reverseEngineeringLevel", 8},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_sds_heavy_imperial_spc_forces_cannon, "object/tangible/ship/components/weapon/wpn_sds_heavy_imperial_spc_forces_cannon.iff")
