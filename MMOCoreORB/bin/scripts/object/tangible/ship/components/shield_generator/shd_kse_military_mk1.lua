object_tangible_ship_components_shield_generator_shd_kse_military_mk1 = object_tangible_ship_components_shield_generator_shared_shd_kse_military_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_kse_military_mk1",

	attributes = {
		{"shieldRechargeRate", 1.52},
		{"shieldHitpointsMaximumFront", 225},
		{"shieldHitpointsMaximumBack", 225},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 2556},
		{"mass", 1100},
		{"reverseEngineeringLevel", 1},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_kse_military_mk1, "object/tangible/ship/components/shield_generator/shd_kse_military_mk1.iff")
