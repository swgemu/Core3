object_tangible_ship_components_shield_generator_shd_incom_techscreen_1 = object_tangible_ship_components_shield_generator_shared_shd_incom_techscreen_1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_incom_techscreen_1",

	attributes = {
		{"shieldRechargeRate", 11.837},
		{"shieldHitpointsMaximumFront", 1557.38},
		{"shieldHitpointsMaximumBack", 1557.38},
		{"currentHitpoints", 1168.04},
		{"maximumHitpoints", 1168.04},
		{"maximumArmorHitpoints", 584.018},
		{"currentArmorHitpoints", 584.018},
		{"efficiency", 1},
		{"energyMaintenance", 2931},
		{"mass", 34534.5},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"shieldRechargeRate", 0.22},
		{"shieldHitpointsMaximumFront", 0.32},
		{"shieldHitpointsMaximumBack", 0.32},
		{"maximumArmorHitpoints", 0.04},
		{"energyMaintenance", 0.2},
		{"mass", 0.1},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_incom_techscreen_1, "object/tangible/ship/components/shield_generator/shd_incom_techscreen_1.iff")
