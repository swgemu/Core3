object_tangible_ship_components_shield_generator_shd_armek_plasma_shell_elite_2 = object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_elite_2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_armek_plasma_shell_elite_2",

	attributes = {
		{"shieldRechargeRate", 13.937},
		{"shieldHitpointsMaximumFront", 1833.97},
		{"shieldHitpointsMaximumBack", 1833.97},
		{"currentHitpoints", 1375.47},
		{"maximumHitpoints", 1375.47},
		{"maximumArmorHitpoints", 687.737},
		{"currentArmorHitpoints", 687.737},
		{"efficiency", 1},
		{"energyMaintenance", 3056},
		{"mass", 62040},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"shieldRechargeRate", 0.22},
		{"shieldHitpointsMaximumFront", 0.32},
		{"shieldHitpointsMaximumBack", 0.32},
		{"maximumArmorHitpoints", 0.04},
		{"energyMaintenance", 0.2},
		{"mass", 0.1},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_armek_plasma_shell_elite_2, "object/tangible/ship/components/shield_generator/shd_armek_plasma_shell_elite_2.iff")
