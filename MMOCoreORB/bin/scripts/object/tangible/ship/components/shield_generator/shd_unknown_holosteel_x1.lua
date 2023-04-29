object_tangible_ship_components_shield_generator_shd_unknown_holosteel_x1 = object_tangible_ship_components_shield_generator_shared_shd_unknown_holosteel_x1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_unknown_holosteel_x1",

	attributes = {
		{"shieldRechargeRate", 3.496},
		{"shieldHitpointsMaximumFront", 460},
		{"shieldHitpointsMaximumBack", 460},
		{"currentHitpoints", 327.75},
		{"maximumHitpoints", 327.75},
		{"maximumArmorHitpoints", 163.875},
		{"currentArmorHitpoints", 163.875},
		{"efficiency", 1},
		{"energyMaintenance", 2681},
		{"mass", 2887.5},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.35},
		{"shieldHitpointsMaximumBack", 0.35},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_unknown_holosteel_x1, "object/tangible/ship/components/shield_generator/shd_unknown_holosteel_x1.iff")
