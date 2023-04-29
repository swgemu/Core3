object_tangible_ship_components_shield_generator_shd_incom_techscreen_2 = object_tangible_ship_components_shield_generator_shared_shd_incom_techscreen_2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_incom_techscreen_2",

	attributes = {
		{"shieldRechargeRate", 11.149},
		{"shieldHitpointsMaximumFront", 1467.18},
		{"shieldHitpointsMaximumBack", 1467.18},
		{"currentHitpoints", 1045.36},
		{"maximumHitpoints", 1045.36},
		{"maximumArmorHitpoints", 522.68},
		{"currentArmorHitpoints", 522.68},
		{"efficiency", 1},
		{"energyMaintenance", 3056},
		{"mass", 53625},
		{"reverseEngineeringLevel", 9},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_incom_techscreen_2, "object/tangible/ship/components/shield_generator/shd_incom_techscreen_2.iff")
