object_tangible_ship_components_shield_generator_shd_phased_fullerine_fx27 = object_tangible_ship_components_shield_generator_shared_shd_phased_fullerine_fx27:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_phased_fullerine_fx27",

	attributes = {
		{"shieldRechargeRate", 8.722},
		{"shieldHitpointsMaximumFront", 1323.77},
		{"shieldHitpointsMaximumBack", 1323.77},
		{"currentHitpoints", 1027.87},
		{"maximumHitpoints", 1027.87},
		{"maximumArmorHitpoints", 513.937},
		{"currentArmorHitpoints", 513.937},
		{"efficiency", 1},
		{"energyMaintenance", 2931},
		{"mass", 22308},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"shieldRechargeRate", 0.27},
		{"shieldHitpointsMaximumFront", 0.33},
		{"shieldHitpointsMaximumBack", 0.33},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_phased_fullerine_fx27, "object/tangible/ship/components/shield_generator/shd_phased_fullerine_fx27.iff")
