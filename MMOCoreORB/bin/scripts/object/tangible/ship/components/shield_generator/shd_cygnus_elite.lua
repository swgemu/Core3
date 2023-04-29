object_tangible_ship_components_shield_generator_shd_cygnus_elite = object_tangible_ship_components_shield_generator_shared_shd_cygnus_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_cygnus_elite",

	attributes = {
		{"shieldRechargeRate", 13.937},
		{"shieldHitpointsMaximumFront", 1833.97},
		{"shieldHitpointsMaximumBack", 1833.97},
		{"currentHitpoints", 1306.7},
		{"maximumHitpoints", 1306.7},
		{"maximumArmorHitpoints", 653.351},
		{"currentArmorHitpoints", 653.351},
		{"efficiency", 1},
		{"energyMaintenance", 3056},
		{"mass", 59455},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.35},
		{"shieldHitpointsMaximumBack", 0.35},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_cygnus_elite, "object/tangible/ship/components/shield_generator/shd_cygnus_elite.iff")
