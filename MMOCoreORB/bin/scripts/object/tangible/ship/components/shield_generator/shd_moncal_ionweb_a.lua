object_tangible_ship_components_shield_generator_shd_moncal_ionweb_a = object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_a:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_moncal_ionweb_a",

	attributes = {
		{"shieldRechargeRate", 1.4},
		{"shieldHitpointsMaximumFront", 212.5},
		{"shieldHitpointsMaximumBack", 212.5},
		{"currentHitpoints", 165},
		{"maximumHitpoints", 165},
		{"maximumArmorHitpoints", 82.5},
		{"currentArmorHitpoints", 82.5},
		{"efficiency", 1},
		{"energyMaintenance", 2556},
		{"mass", 1430},
		{"reverseEngineeringLevel", 1},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_moncal_ionweb_a, "object/tangible/ship/components/shield_generator/shd_moncal_ionweb_a.iff")
