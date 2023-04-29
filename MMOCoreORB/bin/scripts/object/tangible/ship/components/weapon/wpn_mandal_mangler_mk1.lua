object_tangible_ship_components_weapon_wpn_mandal_mangler_mk1 = object_tangible_ship_components_weapon_shared_wpn_mandal_mangler_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_mandal_mangler_mk1",

	attributes = {
		{"minDamage", 298.7},
		{"maxDamage", 401.7},
		{"shieldEffectiveness", 0.5},
		{"armorEffectiveness", 0.5},
		{"energyPerShot", 20.4},
		{"refireRate", 0.34},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 2200},
		{"mass", 1000},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"minDamage", 0.14},
		{"maxDamage", 0.14},
		{"shieldEffectiveness", 0.05},
		{"armorEffectiveness", 0.05},
		{"energyPerShot", 0.17},
		{"refireRate", 0.05},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.17},
		{"mass", 0.17},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_mandal_mangler_mk1, "object/tangible/ship/components/weapon/wpn_mandal_mangler_mk1.iff")
