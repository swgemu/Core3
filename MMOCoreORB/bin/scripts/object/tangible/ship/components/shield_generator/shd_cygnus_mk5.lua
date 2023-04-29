object_tangible_ship_components_shield_generator_shd_cygnus_mk5 = object_tangible_ship_components_shield_generator_shared_shd_cygnus_mk5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_cygnus_mk5",

	attributes = {
		{"shieldRechargeRate", 12.029},
		{"shieldHitpointsMaximumFront", 1467.18},
		{"shieldHitpointsMaximumBack", 1467.18},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 3056},
		{"mass", 51480},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"shieldRechargeRate", 0.15},
		{"shieldHitpointsMaximumFront", 0.345},
		{"shieldHitpointsMaximumBack", 0.345},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_cygnus_mk5, "object/tangible/ship/components/shield_generator/shd_cygnus_mk5.iff")
