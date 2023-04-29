object_tangible_ship_components_shield_generator_shd_seinar_gx3 = object_tangible_ship_components_shield_generator_shared_shd_seinar_gx3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_seinar_gx3",

	attributes = {
		{"shieldRechargeRate", 1.52},
		{"shieldHitpointsMaximumFront", 200},
		{"shieldHitpointsMaximumBack", 200},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 2556},
		{"mass", 1210},
		{"reverseEngineeringLevel", 1},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_seinar_gx3, "object/tangible/ship/components/shield_generator/shd_seinar_gx3.iff")
