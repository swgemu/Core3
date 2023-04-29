object_tangible_ship_components_shield_generator_shd_moncal_ionweb_elite_2 = object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_elite_2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_moncal_ionweb_elite_2",

	attributes = {
		{"shieldRechargeRate", 15.037},
		{"shieldHitpointsMaximumFront", 1833.97},
		{"shieldHitpointsMaximumBack", 1833.97},
		{"currentHitpoints", 1375.47},
		{"maximumHitpoints", 1375.47},
		{"maximumArmorHitpoints", 687.737},
		{"currentArmorHitpoints", 687.737},
		{"efficiency", 1},
		{"energyMaintenance", 3056},
		{"mass", 72380},
		{"reverseEngineeringLevel", 10},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_moncal_ionweb_elite_2, "object/tangible/ship/components/shield_generator/shd_moncal_ionweb_elite_2.iff")
