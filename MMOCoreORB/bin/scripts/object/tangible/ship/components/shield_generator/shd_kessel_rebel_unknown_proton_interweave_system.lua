object_tangible_ship_components_shield_generator_shd_kessel_rebel_unknown_proton_interweave_system = object_tangible_ship_components_shield_generator_shared_shd_kessel_rebel_unknown_proton_interweave_system:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_kessel_rebel_unknown_proton_interweave_system",

	attributes = {
		{"shieldRechargeRate", 12.47},
		{"shieldHitpointsMaximumFront", 1467.18},
		{"shieldHitpointsMaximumBack", 1467.18},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 3125},
		{"mass", 51480},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.341},
		{"shieldHitpointsMaximumBack", 0.341},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.35},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_kessel_rebel_unknown_proton_interweave_system, "object/tangible/ship/components/shield_generator/shd_kessel_rebel_unknown_proton_interweave_system.iff")
