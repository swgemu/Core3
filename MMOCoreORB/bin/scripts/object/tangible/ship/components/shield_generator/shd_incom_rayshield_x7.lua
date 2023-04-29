object_tangible_ship_components_shield_generator_shd_incom_rayshield_x7 = object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x7:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_incom_rayshield_x7",

	attributes = {
		{"shieldRechargeRate", 4.025},
		{"shieldHitpointsMaximumFront", 610.938},
		{"shieldHitpointsMaximumBack", 610.938},
		{"currentHitpoints", 474.375},
		{"maximumHitpoints", 474.375},
		{"maximumArmorHitpoints", 237.188},
		{"currentArmorHitpoints", 237.188},
		{"efficiency", 1},
		{"energyMaintenance", 2681},
		{"mass", 6256.25},
		{"reverseEngineeringLevel", 4},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_incom_rayshield_x7, "object/tangible/ship/components/shield_generator/shd_incom_rayshield_x7.iff")
