object_tangible_ship_components_shield_generator_shd_incom_rayshield_x12 = object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x12:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_incom_rayshield_x12",

	attributes = {
		{"shieldRechargeRate", 6.43},
		{"shieldHitpointsMaximumFront", 952.2},
		{"shieldHitpointsMaximumBack", 952.2},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 2806},
		{"mass", 7562.5},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.2},
		{"shieldHitpointsMaximumBack", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_incom_rayshield_x12, "object/tangible/ship/components/shield_generator/shd_incom_rayshield_x12.iff")
