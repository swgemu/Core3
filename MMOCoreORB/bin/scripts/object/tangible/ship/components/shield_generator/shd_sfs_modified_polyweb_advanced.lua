object_tangible_ship_components_shield_generator_shd_sfs_modified_polyweb_advanced = object_tangible_ship_components_shield_generator_shared_shd_sfs_modified_polyweb_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_sfs_modified_polyweb_advanced",

	attributes = {
		{"shieldRechargeRate", 12.029},
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
		{"shieldRechargeRate", 0.15},
		{"shieldHitpointsMaximumFront", 0.341},
		{"shieldHitpointsMaximumBack", 0.341},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_sfs_modified_polyweb_advanced, "object/tangible/ship/components/shield_generator/shd_sfs_modified_polyweb_advanced.iff")
