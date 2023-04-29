object_tangible_ship_components_shield_generator_shd_taim_enhanced_advanced = object_tangible_ship_components_shield_generator_shared_shd_taim_enhanced_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_taim_enhanced_advanced",

	attributes = {
		{"shieldRechargeRate", 10.269},
		{"shieldHitpointsMaximumFront", 1283.78},
		{"shieldHitpointsMaximumBack", 1283.78},
		{"currentHitpoints", 1430.49},
		{"maximumHitpoints", 1430.49},
		{"maximumArmorHitpoints", 715.247},
		{"currentArmorHitpoints", 715.247},
		{"efficiency", 1},
		{"energyMaintenance", 3056},
		{"mass", 60060},
		{"reverseEngineeringLevel", 9},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_taim_enhanced_advanced, "object/tangible/ship/components/shield_generator/shd_taim_enhanced_advanced.iff")
