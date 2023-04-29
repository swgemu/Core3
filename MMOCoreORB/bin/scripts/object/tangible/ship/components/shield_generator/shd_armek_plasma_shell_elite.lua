object_tangible_ship_components_shield_generator_shd_armek_plasma_shell_elite = object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_armek_plasma_shell_elite",

	attributes = {
		{"shieldRechargeRate", 10.269},
		{"shieldHitpointsMaximumFront", 1558.87},
		{"shieldHitpointsMaximumBack", 1558.87},
		{"currentHitpoints", 1210.42},
		{"maximumHitpoints", 1210.42},
		{"maximumArmorHitpoints", 605.209},
		{"currentArmorHitpoints", 605.209},
		{"efficiency", 1},
		{"energyMaintenance", 3056},
		{"mass", 64350},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"shieldRechargeRate", 0.27},
		{"shieldHitpointsMaximumFront", 0.33},
		{"shieldHitpointsMaximumBack", 0.33},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_armek_plasma_shell_elite, "object/tangible/ship/components/shield_generator/shd_armek_plasma_shell_elite.iff")
