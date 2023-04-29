object_tangible_ship_components_shield_generator_shd_taim_heavy = object_tangible_ship_components_shield_generator_shared_shd_taim_heavy:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_taim_heavy",

	attributes = {
		{"shieldRechargeRate", 9.47},
		{"shieldHitpointsMaximumFront", 1245.9},
		{"shieldHitpointsMaximumBack", 1245.9},
		{"currentHitpoints", 887.708},
		{"maximumHitpoints", 887.708},
		{"maximumArmorHitpoints", 443.854},
		{"currentArmorHitpoints", 443.854},
		{"efficiency", 1},
		{"energyMaintenance", 2931},
		{"mass", 19819.8},
		{"reverseEngineeringLevel", 7},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_taim_heavy, "object/tangible/ship/components/shield_generator/shd_taim_heavy.iff")
