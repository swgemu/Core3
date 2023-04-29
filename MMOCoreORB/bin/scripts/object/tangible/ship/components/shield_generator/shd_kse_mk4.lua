object_tangible_ship_components_shield_generator_shd_kse_mk4 = object_tangible_ship_components_shield_generator_shared_shd_kse_mk4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_kse_mk4",

	attributes = {
		{"shieldRechargeRate", 8.037},
		{"shieldHitpointsMaximumFront", 1190.25},
		{"shieldHitpointsMaximumBack", 1190.25},
		{"currentHitpoints", 793.5},
		{"maximumHitpoints", 793.5},
		{"maximumArmorHitpoints", 396.75},
		{"currentArmorHitpoints", 396.75},
		{"efficiency", 1},
		{"energyMaintenance", 2806},
		{"mass", 13219.2},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.2},
		{"shieldHitpointsMaximumBack", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_kse_mk4, "object/tangible/ship/components/shield_generator/shd_kse_mk4.iff")
