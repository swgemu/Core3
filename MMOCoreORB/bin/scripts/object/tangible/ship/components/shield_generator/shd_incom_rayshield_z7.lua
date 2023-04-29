object_tangible_ship_components_shield_generator_shd_incom_rayshield_z7 = object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_z7:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_incom_rayshield_z7",

	attributes = {
		{"shieldRechargeRate", 8.037},
		{"shieldHitpointsMaximumFront", 1058},
		{"shieldHitpointsMaximumBack", 1058},
		{"currentHitpoints", 714.15},
		{"maximumHitpoints", 714.15},
		{"maximumArmorHitpoints", 357.075},
		{"currentArmorHitpoints", 357.075},
		{"efficiency", 1},
		{"energyMaintenance", 2875},
		{"mass", 14421},
		{"reverseEngineeringLevel", 6},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_incom_rayshield_z7, "object/tangible/ship/components/shield_generator/shd_incom_rayshield_z7.iff")
