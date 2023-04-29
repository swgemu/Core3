object_tangible_ship_components_weapon_wpn_mandal_enhanced_mangler_mk1 = object_tangible_ship_components_weapon_shared_wpn_mandal_enhanced_mangler_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_mandal_enhanced_mangler_mk1",

	attributes = {
		{"minDamage", 373.375},
		{"maxDamage", 502.125},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 25.5},
		{"refireRate", 0.425},
		{"currentHitpoints", 225},
		{"maximumHitpoints", 225},
		{"maximumArmorHitpoints", 112.5},
		{"currentArmorHitpoints", 112.5},
		{"efficiency", 1},
		{"energyMaintenance", 2000},
		{"mass", 1925},
		{"reverseEngineeringLevel", 2},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_mandal_enhanced_mangler_mk1, "object/tangible/ship/components/weapon/wpn_mandal_enhanced_mangler_mk1.iff")
