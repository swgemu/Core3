object_tangible_ship_components_shield_generator_shd_kse_elite = object_tangible_ship_components_shield_generator_shared_shd_kse_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_kse_elite",

	attributes = {
		{"shieldRechargeRate", 13.937},
		{"shieldHitpointsMaximumFront", 1833.97},
		{"shieldHitpointsMaximumBack", 1833.97},
		{"currentHitpoints", 1237.93},
		{"maximumHitpoints", 1237.93},
		{"maximumArmorHitpoints", 618.964},
		{"currentArmorHitpoints", 618.964},
		{"efficiency", 1},
		{"energyMaintenance", 3000},
		{"mass", 67210},
		{"reverseEngineeringLevel", 10},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_kse_elite, "object/tangible/ship/components/shield_generator/shd_kse_elite.iff")
