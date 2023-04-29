object_tangible_ship_components_shield_generator_shd_mandalor_flexshield_ks3 = object_tangible_ship_components_shield_generator_shared_shd_mandalor_flexshield_ks3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_mandalor_flexshield_ks3",

	attributes = {
		{"shieldRechargeRate", 4.025},
		{"shieldHitpointsMaximumFront", 503.125},
		{"shieldHitpointsMaximumBack", 503.125},
		{"currentHitpoints", 560.625},
		{"maximumHitpoints", 560.625},
		{"maximumArmorHitpoints", 280.312},
		{"currentArmorHitpoints", 280.312},
		{"efficiency", 1},
		{"energyMaintenance", 2681},
		{"mass", 5775},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.341},
		{"shieldHitpointsMaximumBack", 0.341},
		{"maximumArmorHitpoints", 0.07},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_mandalor_flexshield_ks3, "object/tangible/ship/components/shield_generator/shd_mandalor_flexshield_ks3.iff")
