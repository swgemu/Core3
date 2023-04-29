object_tangible_ship_components_shield_generator_shd_incom_rayshield_z5 = object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_z5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_incom_rayshield_z5",

	attributes = {
		{"shieldRechargeRate", 8.037},
		{"shieldHitpointsMaximumFront", 1058},
		{"shieldHitpointsMaximumBack", 1058},
		{"currentHitpoints", 753.825},
		{"maximumHitpoints", 753.825},
		{"maximumArmorHitpoints", 376.913},
		{"currentArmorHitpoints", 376.913},
		{"efficiency", 1},
		{"energyMaintenance", 2806},
		{"mass", 13820.1},
		{"reverseEngineeringLevel", 6},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_incom_rayshield_z5, "object/tangible/ship/components/shield_generator/shd_incom_rayshield_z5.iff")
