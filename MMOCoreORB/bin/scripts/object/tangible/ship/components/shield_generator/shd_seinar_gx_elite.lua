object_tangible_ship_components_shield_generator_shd_seinar_gx_elite = object_tangible_ship_components_shield_generator_shared_shd_seinar_gx_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_seinar_gx_elite",

	attributes = {
		{"shieldRechargeRate", 1.52},
		{"shieldHitpointsMaximumFront", 200},
		{"shieldHitpointsMaximumBack", 200},
		{"currentHitpoints", 135},
		{"maximumHitpoints", 135},
		{"maximumArmorHitpoints", 67.5},
		{"currentArmorHitpoints", 67.5},
		{"efficiency", 1},
		{"energyMaintenance", 2625},
		{"mass", 1210},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"shieldRechargeRate", 0.27},
		{"shieldHitpointsMaximumFront", 0.35},
		{"shieldHitpointsMaximumBack", 0.35},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_seinar_gx_elite, "object/tangible/ship/components/shield_generator/shd_seinar_gx_elite.iff")
