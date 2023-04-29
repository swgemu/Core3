object_tangible_ship_components_shield_generator_shd_mandal_protector_mk1 = object_tangible_ship_components_shield_generator_shared_shd_mandal_protector_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_mandal_protector_mk1",

	attributes = {
		{"shieldRechargeRate", 1.4},
		{"shieldHitpointsMaximumFront", 175},
		{"shieldHitpointsMaximumBack", 175},
		{"currentHitpoints", 195},
		{"maximumHitpoints", 195},
		{"maximumArmorHitpoints", 97.5},
		{"currentArmorHitpoints", 97.5},
		{"efficiency", 1},
		{"energyMaintenance", 2556},
		{"mass", 1320},
		{"reverseEngineeringLevel", 1},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_mandal_protector_mk1, "object/tangible/ship/components/shield_generator/shd_mandal_protector_mk1.iff")
