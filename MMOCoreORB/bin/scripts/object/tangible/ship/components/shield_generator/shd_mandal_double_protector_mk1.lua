object_tangible_ship_components_shield_generator_shd_mandal_double_protector_mk1 = object_tangible_ship_components_shield_generator_shared_shd_mandal_double_protector_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_mandal_double_protector_mk1",

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
		{"mass", 2117.5},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"shieldRechargeRate", 0.24},
		{"shieldHitpointsMaximumFront", 0.341},
		{"shieldHitpointsMaximumBack", 0.341},
		{"maximumArmorHitpoints", 0.03},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_mandal_double_protector_mk1, "object/tangible/ship/components/shield_generator/shd_mandal_double_protector_mk1.iff")
