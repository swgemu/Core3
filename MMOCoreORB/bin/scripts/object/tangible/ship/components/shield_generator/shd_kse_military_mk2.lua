object_tangible_ship_components_shield_generator_shd_kse_military_mk2 = object_tangible_ship_components_shield_generator_shared_shd_kse_military_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_kse_military_mk2",

	attributes = {
		{"shieldRechargeRate", 3.496},
		{"shieldHitpointsMaximumFront", 460},
		{"shieldHitpointsMaximumBack", 460},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 2681},
		{"mass", 2887.5},
		{"reverseEngineeringLevel", 3},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_kse_military_mk2, "object/tangible/ship/components/shield_generator/shd_kse_military_mk2.iff")
