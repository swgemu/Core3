object_tangible_ship_components_shield_generator_shd_incom_rayshield_x1 = object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_incom_rayshield_x1",

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
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.341},
		{"shieldHitpointsMaximumBack", 0.341},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.1},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_incom_rayshield_x1, "object/tangible/ship/components/shield_generator/shd_incom_rayshield_x1.iff")
