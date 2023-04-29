object_tangible_ship_components_weapon_wpn_taim_kx8 = object_tangible_ship_components_weapon_shared_wpn_taim_kx8:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_taim_kx8",

	attributes = {
		{"minDamage", 1591.82},
		{"maxDamage", 2461.33},
		{"shieldEffectiveness", 0.6},
		{"armorEffectiveness", 0.45},
		{"energyPerShot", 27.156},
		{"refireRate", 0.34},
		{"currentHitpoints", 840.987},
		{"maximumHitpoints", 840.987},
		{"maximumArmorHitpoints", 420.493},
		{"currentArmorHitpoints", 420.493},
		{"efficiency", 1},
		{"energyMaintenance", 2300},
		{"mass", 16380},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_taim_kx8, "object/tangible/ship/components/weapon/wpn_taim_kx8.iff")
