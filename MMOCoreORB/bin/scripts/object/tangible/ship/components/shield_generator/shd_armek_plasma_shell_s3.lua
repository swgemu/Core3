object_tangible_ship_components_shield_generator_shd_armek_plasma_shell_s3 = object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_s3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_armek_plasma_shell_s3",

	attributes = {
		{"shieldRechargeRate", 6.43},
		{"shieldHitpointsMaximumFront", 846.4},
		{"shieldHitpointsMaximumBack", 846.4},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 2806},
		{"mass", 7562.5},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.341},
		{"shieldHitpointsMaximumBack", 0.341},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.2},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_armek_plasma_shell_s3, "object/tangible/ship/components/shield_generator/shd_armek_plasma_shell_s3.iff")
