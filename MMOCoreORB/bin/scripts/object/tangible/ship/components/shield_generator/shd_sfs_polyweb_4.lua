object_tangible_ship_components_shield_generator_shd_sfs_polyweb_4 = object_tangible_ship_components_shield_generator_shared_shd_sfs_polyweb_4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_sfs_polyweb_4",

	attributes = {
		{"shieldRechargeRate", 11.837},
		{"shieldHitpointsMaximumFront", 1752.05},
		{"shieldHitpointsMaximumBack", 1752.05},
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
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.2},
		{"shieldHitpointsMaximumBack", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_sfs_polyweb_4, "object/tangible/ship/components/shield_generator/shd_sfs_polyweb_4.iff")
