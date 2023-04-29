object_tangible_ship_components_shield_generator_shd_kessel_imperial_sds_secret_ops = object_tangible_ship_components_shield_generator_shared_shd_kessel_imperial_sds_secret_ops:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_kessel_imperial_sds_secret_ops",

	attributes = {
		{"shieldRechargeRate", 12.836},
		{"shieldHitpointsMaximumFront", 1948.59},
		{"shieldHitpointsMaximumBack", 1948.59},
		{"currentHitpoints", 1513.02},
		{"maximumHitpoints", 1513.02},
		{"maximumArmorHitpoints", 756.511},
		{"currentArmorHitpoints", 756.511},
		{"efficiency", 1},
		{"energyMaintenance", 3056},
		{"mass", 77550},
		{"reverseEngineeringLevel", 10},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_kessel_imperial_sds_secret_ops, "object/tangible/ship/components/shield_generator/shd_kessel_imperial_sds_secret_ops.iff")
