object_tangible_ship_components_shield_generator_shd_moncal_ionweb_elite = object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_moncal_ionweb_elite",

	attributes = {
		{"shieldRechargeRate", 11.149},
		{"shieldHitpointsMaximumFront", 1650.57},
		{"shieldHitpointsMaximumBack", 1650.57},
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
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.2},
		{"shieldHitpointsMaximumBack", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_moncal_ionweb_elite, "object/tangible/ship/components/shield_generator/shd_moncal_ionweb_elite.iff")
