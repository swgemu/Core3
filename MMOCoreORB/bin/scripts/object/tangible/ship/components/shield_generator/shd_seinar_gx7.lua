object_tangible_ship_components_shield_generator_shd_seinar_gx7 = object_tangible_ship_components_shield_generator_shared_shd_seinar_gx7:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_seinar_gx7",

	attributes = {
		{"shieldRechargeRate", 1.52},
		{"shieldHitpointsMaximumFront", 200},
		{"shieldHitpointsMaximumBack", 200},
		{"currentHitpoints", 142.5},
		{"maximumHitpoints", 142.5},
		{"maximumArmorHitpoints", 71.25},
		{"currentArmorHitpoints", 71.25},
		{"efficiency", 1},
		{"energyMaintenance", 2556},
		{"mass", 1155},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_seinar_gx7, "object/tangible/ship/components/shield_generator/shd_seinar_gx7.iff")
