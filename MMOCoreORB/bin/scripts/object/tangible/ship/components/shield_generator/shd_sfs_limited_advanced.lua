object_tangible_ship_components_shield_generator_shd_sfs_limited_advanced = object_tangible_ship_components_shield_generator_shared_shd_sfs_limited_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_sfs_limited_advanced",

	attributes = {
		{"shieldRechargeRate", 8.672},
		{"shieldHitpointsMaximumFront", 1058},
		{"shieldHitpointsMaximumBack", 1058},
		{"currentHitpoints", 793.5},
		{"maximumHitpoints", 793.5},
		{"maximumArmorHitpoints", 396.75},
		{"currentArmorHitpoints", 396.75},
		{"efficiency", 1},
		{"energyMaintenance", 2806},
		{"mass", 13219.2},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"shieldRechargeRate", 0.15},
		{"shieldHitpointsMaximumFront", 0.345},
		{"shieldHitpointsMaximumBack", 0.345},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_sfs_limited_advanced, "object/tangible/ship/components/shield_generator/shd_sfs_limited_advanced.iff")
