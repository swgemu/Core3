object_tangible_ship_components_shield_generator_shd_armek_plasma_shell_s1 = object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_s1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_armek_plasma_shell_s1",

	attributes = {
		{"shieldRechargeRate", 1.66},
		{"shieldHitpointsMaximumFront", 200},
		{"shieldHitpointsMaximumBack", 200},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 2750},
		{"mass", 1100},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.341},
		{"shieldHitpointsMaximumBack", 0.341},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.35},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_armek_plasma_shell_s1, "object/tangible/ship/components/shield_generator/shd_armek_plasma_shell_s1.iff")
