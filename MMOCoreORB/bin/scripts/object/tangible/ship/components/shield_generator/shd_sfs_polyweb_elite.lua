object_tangible_ship_components_shield_generator_shd_sfs_polyweb_elite = object_tangible_ship_components_shield_generator_shared_shd_sfs_polyweb_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_sfs_polyweb_elite",

	attributes = {
		{"shieldRechargeRate", 13.937},
		{"shieldHitpointsMaximumFront", 1833.97},
		{"shieldHitpointsMaximumBack", 1833.97},
		{"currentHitpoints", 1375.47},
		{"maximumHitpoints", 1375.47},
		{"maximumArmorHitpoints", 687.737},
		{"currentArmorHitpoints", 687.737},
		{"efficiency", 1},
		{"energyMaintenance", 3056},
		{"mass", 77550},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"shieldRechargeRate", 0.28},
		{"shieldHitpointsMaximumFront", 0.341},
		{"shieldHitpointsMaximumBack", 0.341},
		{"maximumArmorHitpoints", 0.03},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_sfs_polyweb_elite, "object/tangible/ship/components/shield_generator/shd_sfs_polyweb_elite.iff")
