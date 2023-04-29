object_tangible_ship_components_shield_generator_shd_kse_mk7 = object_tangible_ship_components_shield_generator_shared_shd_kse_mk7:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_kse_mk7",

	attributes = {
		{"shieldRechargeRate", 11.149},
		{"shieldHitpointsMaximumFront", 1467.18},
		{"shieldHitpointsMaximumBack", 1467.18},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 3056},
		{"mass", 51480},
		{"reverseEngineeringLevel", 9},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_kse_mk7, "object/tangible/ship/components/shield_generator/shd_kse_mk7.iff")
