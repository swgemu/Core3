object_tangible_ship_components_shield_generator_shd_sfs_imperial_heavy = object_tangible_ship_components_shield_generator_shared_shd_sfs_imperial_heavy:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_sfs_imperial_heavy",

	attributes = {
		{"shieldRechargeRate", 5.922},
		{"shieldHitpointsMaximumFront", 899.3},
		{"shieldHitpointsMaximumBack", 899.3},
		{"currentHitpoints", 698.28},
		{"maximumHitpoints", 698.28},
		{"maximumArmorHitpoints", 349.14},
		{"currentArmorHitpoints", 349.14},
		{"efficiency", 1},
		{"energyMaintenance", 2806},
		{"mass", 9625},
		{"reverseEngineeringLevel", 5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_sfs_imperial_heavy, "object/tangible/ship/components/shield_generator/shd_sfs_imperial_heavy.iff")
