object_tangible_ship_components_shield_generator_shd_sfs_polyweb_advanced = object_tangible_ship_components_shield_generator_shared_shd_sfs_polyweb_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_sfs_polyweb_advanced",

	attributes = {
		{"shieldRechargeRate", 11.149},
		{"shieldHitpointsMaximumFront", 1467.18},
		{"shieldHitpointsMaximumBack", 1467.18},
		{"currentHitpoints", 990.342},
		{"maximumHitpoints", 990.342},
		{"maximumArmorHitpoints", 495.171},
		{"currentArmorHitpoints", 495.171},
		{"efficiency", 1},
		{"energyMaintenance", 3000},
		{"mass", 55770},
		{"reverseEngineeringLevel", 9},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_sfs_polyweb_advanced, "object/tangible/ship/components/shield_generator/shd_sfs_polyweb_advanced.iff")
