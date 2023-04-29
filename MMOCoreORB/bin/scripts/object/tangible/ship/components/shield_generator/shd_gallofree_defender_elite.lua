object_tangible_ship_components_shield_generator_shd_gallofree_defender_elite = object_tangible_ship_components_shield_generator_shared_shd_gallofree_defender_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_gallofree_defender_elite",

	attributes = {
		{"shieldRechargeRate", 13.937},
		{"shieldHitpointsMaximumFront", 2063.22},
		{"shieldHitpointsMaximumBack", 2063.22},
		{"currentHitpoints", 1375.47},
		{"maximumHitpoints", 1375.47},
		{"maximumArmorHitpoints", 687.737},
		{"currentArmorHitpoints", 687.737},
		{"efficiency", 1},
		{"energyMaintenance", 3056},
		{"mass", 62040},
		{"reverseEngineeringLevel", 10},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_gallofree_defender_elite, "object/tangible/ship/components/shield_generator/shd_gallofree_defender_elite.iff")
