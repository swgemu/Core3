object_tangible_ship_components_shield_generator_shd_interlaced_graviton = object_tangible_ship_components_shield_generator_shared_shd_interlaced_graviton:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_interlaced_graviton",

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
		{"mass", 64350},
		{"reverseEngineeringLevel", 9},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_interlaced_graviton, "object/tangible/ship/components/shield_generator/shd_interlaced_graviton.iff")
