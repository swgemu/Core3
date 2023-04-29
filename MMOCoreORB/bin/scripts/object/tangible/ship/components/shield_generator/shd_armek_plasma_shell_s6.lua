object_tangible_ship_components_shield_generator_shd_armek_plasma_shell_s6 = object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_s6:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_armek_plasma_shell_s6",

	attributes = {
		{"shieldRechargeRate", 7.403},
		{"shieldHitpointsMaximumFront", 925.75},
		{"shieldHitpointsMaximumBack", 925.75},
		{"currentHitpoints", 1031.55},
		{"maximumHitpoints", 1031.55},
		{"maximumArmorHitpoints", 515.775},
		{"currentArmorHitpoints", 515.775},
		{"efficiency", 1},
		{"energyMaintenance", 2806},
		{"mass", 15622.8},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.341},
		{"shieldHitpointsMaximumBack", 0.341},
		{"maximumArmorHitpoints", 0.07},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_armek_plasma_shell_s6, "object/tangible/ship/components/shield_generator/shd_armek_plasma_shell_s6.iff")
