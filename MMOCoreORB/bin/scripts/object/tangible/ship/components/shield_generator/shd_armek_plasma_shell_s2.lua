object_tangible_ship_components_shield_generator_shd_armek_plasma_shell_s2 = object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_s2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_armek_plasma_shell_s2",

	attributes = {
		{"shieldRechargeRate", 2.05},
		{"shieldHitpointsMaximumFront", 250},
		{"shieldHitpointsMaximumBack", 250},
		{"currentHitpoints", 187.5},
		{"maximumHitpoints", 187.5},
		{"maximumArmorHitpoints", 93.75},
		{"currentArmorHitpoints", 93.75},
		{"efficiency", 1},
		{"energyMaintenance", 2556},
		{"mass", 1925},
		{"reverseEngineeringLevel", 2},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_armek_plasma_shell_s2, "object/tangible/ship/components/shield_generator/shd_armek_plasma_shell_s2.iff")
