object_tangible_ship_components_shield_generator_shd_cygnus_mk3 = object_tangible_ship_components_shield_generator_shared_shd_cygnus_mk3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_cygnus_mk3",

	attributes = {
		{"shieldRechargeRate", 8.037},
		{"shieldHitpointsMaximumFront", 1058},
		{"shieldHitpointsMaximumBack", 1058},
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
		{"shieldRechargeRate", 0.22},
		{"shieldHitpointsMaximumFront", 0.32},
		{"shieldHitpointsMaximumBack", 0.32},
		{"maximumArmorHitpoints", 0.04},
		{"energyMaintenance", 0.2},
		{"mass", 0.1},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_cygnus_mk3, "object/tangible/ship/components/shield_generator/shd_cygnus_mk3.iff")
