object_tangible_ship_components_shield_generator_shd_kse_enhanced_military_mk1 = object_tangible_ship_components_shield_generator_shared_shd_kse_enhanced_military_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_kse_enhanced_military_mk1",

	attributes = {
		{"shieldRechargeRate", 1.9},
		{"shieldHitpointsMaximumFront", 250},
		{"shieldHitpointsMaximumBack", 250},
		{"currentHitpoints", 187.5},
		{"maximumHitpoints", 187.5},
		{"maximumArmorHitpoints", 93.75},
		{"currentArmorHitpoints", 93.75},
		{"efficiency", 1},
		{"energyMaintenance", 2556},
		{"mass", 1925},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.341},
		{"shieldHitpointsMaximumBack", 0.341},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.2},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_kse_enhanced_military_mk1, "object/tangible/ship/components/shield_generator/shd_kse_enhanced_military_mk1.iff")
