object_tangible_ship_components_shield_generator_shd_moncal_deluxe_ionweb_b = object_tangible_ship_components_shield_generator_shared_shd_moncal_deluxe_ionweb_b:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_moncal_deluxe_ionweb_b",

	attributes = {
		{"shieldRechargeRate", 3.496},
		{"shieldHitpointsMaximumFront", 517.5},
		{"shieldHitpointsMaximumBack", 517.5},
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
		{"shieldHitpointsMaximumFront", 0.2},
		{"shieldHitpointsMaximumBack", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_moncal_deluxe_ionweb_b, "object/tangible/ship/components/shield_generator/shd_moncal_deluxe_ionweb_b.iff")
