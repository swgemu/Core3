object_tangible_ship_components_shield_generator_shd_cygnus_mk4 = object_tangible_ship_components_shield_generator_shared_shd_cygnus_mk4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_cygnus_mk4",

	attributes = {
		{"shieldRechargeRate", 9.47},
		{"shieldHitpointsMaximumFront", 1245.9},
		{"shieldHitpointsMaximumBack", 1245.9},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 2931},
		{"mass", 23166},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.341},
		{"shieldHitpointsMaximumBack", 0.341},
		{"maximumArmorHitpoints", 0.03},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_cygnus_mk4, "object/tangible/ship/components/shield_generator/shd_cygnus_mk4.iff")
