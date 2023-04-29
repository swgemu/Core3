object_tangible_ship_components_shield_generator_shd_moncal_ionweb_advanced = object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_moncal_ionweb_advanced",

	attributes = {
		{"shieldRechargeRate", 13.239},
		{"shieldHitpointsMaximumFront", 1557.38},
		{"shieldHitpointsMaximumBack", 1557.38},
		{"currentHitpoints", 1168.04},
		{"maximumHitpoints", 1168.04},
		{"maximumArmorHitpoints", 584.018},
		{"currentArmorHitpoints", 584.018},
		{"efficiency", 1},
		{"energyMaintenance", 3125},
		{"mass", 34534.5},
		{"reverseEngineeringLevel", 8},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_moncal_ionweb_advanced, "object/tangible/ship/components/shield_generator/shd_moncal_ionweb_advanced.iff")
