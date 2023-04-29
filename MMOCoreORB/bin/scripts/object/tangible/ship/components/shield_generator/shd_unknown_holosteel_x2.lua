object_tangible_ship_components_shield_generator_shd_unknown_holosteel_x2 = object_tangible_ship_components_shield_generator_shared_shd_unknown_holosteel_x2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_unknown_holosteel_x2",

	attributes = {
		{"shieldRechargeRate", 3.496},
		{"shieldHitpointsMaximumFront", 460},
		{"shieldHitpointsMaximumBack", 460},
		{"currentHitpoints", 310.5},
		{"maximumHitpoints", 310.5},
		{"maximumArmorHitpoints", 155.25},
		{"currentArmorHitpoints", 155.25},
		{"efficiency", 1},
		{"energyMaintenance", 2750},
		{"mass", 3025},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"shieldRechargeRate", 0.27},
		{"shieldHitpointsMaximumFront", 0.35},
		{"shieldHitpointsMaximumBack", 0.35},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_unknown_holosteel_x2, "object/tangible/ship/components/shield_generator/shd_unknown_holosteel_x2.iff")
