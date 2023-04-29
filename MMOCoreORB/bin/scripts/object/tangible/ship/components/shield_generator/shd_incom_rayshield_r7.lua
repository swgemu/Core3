object_tangible_ship_components_shield_generator_shd_incom_rayshield_r7 = object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_r7:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_incom_rayshield_r7",

	attributes = {
		{"shieldRechargeRate", 1.9},
		{"shieldHitpointsMaximumFront", 250},
		{"shieldHitpointsMaximumBack", 250},
		{"currentHitpoints", 178.125},
		{"maximumHitpoints", 178.125},
		{"maximumArmorHitpoints", 89.0625},
		{"currentArmorHitpoints", 89.0625},
		{"efficiency", 1},
		{"energyMaintenance", 2556},
		{"mass", 2021.25},
		{"reverseEngineeringLevel", 2},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_incom_rayshield_r7, "object/tangible/ship/components/shield_generator/shd_incom_rayshield_r7.iff")
