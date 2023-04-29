object_tangible_ship_components_shield_generator_shd_incom_rayshield_z1 = object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_z1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_incom_rayshield_z1",

	attributes = {
		{"shieldRechargeRate", 5.922},
		{"shieldHitpointsMaximumFront", 740.6},
		{"shieldHitpointsMaximumBack", 740.6},
		{"currentHitpoints", 825.24},
		{"maximumHitpoints", 825.24},
		{"maximumArmorHitpoints", 412.62},
		{"currentArmorHitpoints", 412.62},
		{"efficiency", 1},
		{"energyMaintenance", 2806},
		{"mass", 8937.5},
		{"reverseEngineeringLevel", 5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_incom_rayshield_z1, "object/tangible/ship/components/shield_generator/shd_incom_rayshield_z1.iff")
