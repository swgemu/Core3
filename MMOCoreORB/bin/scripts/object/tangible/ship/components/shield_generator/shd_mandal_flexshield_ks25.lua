object_tangible_ship_components_shield_generator_shd_mandal_flexshield_ks25 = object_tangible_ship_components_shield_generator_shared_shd_mandal_flexshield_ks25:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_mandal_flexshield_ks25",

	attributes = {
		{"shieldRechargeRate", 8.037},
		{"shieldHitpointsMaximumFront", 1058},
		{"shieldHitpointsMaximumBack", 1058},
		{"currentHitpoints", 793.5},
		{"maximumHitpoints", 793.5},
		{"maximumArmorHitpoints", 396.75},
		{"currentArmorHitpoints", 396.75},
		{"efficiency", 1},
		{"energyMaintenance", 2806},
		{"mass", 16824.5},
		{"reverseEngineeringLevel", 6},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_mandal_flexshield_ks25, "object/tangible/ship/components/shield_generator/shd_mandal_flexshield_ks25.iff")
