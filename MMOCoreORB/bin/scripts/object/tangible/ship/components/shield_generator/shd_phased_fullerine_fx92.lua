object_tangible_ship_components_shield_generator_shd_phased_fullerine_fx92 = object_tangible_ship_components_shield_generator_shared_shd_phased_fullerine_fx92:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_phased_fullerine_fx92",

	attributes = {
		{"shieldRechargeRate", 11.837},
		{"shieldHitpointsMaximumFront", 1557.38},
		{"shieldHitpointsMaximumBack", 1557.38},
		{"currentHitpoints", 1051.23},
		{"maximumHitpoints", 1051.23},
		{"maximumArmorHitpoints", 525.617},
		{"currentArmorHitpoints", 525.617},
		{"efficiency", 1},
		{"energyMaintenance", 3000},
		{"mass", 37537.5},
		{"reverseEngineeringLevel", 8},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_phased_fullerine_fx92, "object/tangible/ship/components/shield_generator/shd_phased_fullerine_fx92.iff")
