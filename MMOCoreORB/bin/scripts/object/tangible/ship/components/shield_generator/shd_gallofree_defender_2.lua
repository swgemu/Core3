object_tangible_ship_components_shield_generator_shd_gallofree_defender_2 = object_tangible_ship_components_shield_generator_shared_shd_gallofree_defender_2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_gallofree_defender_2",

	attributes = {
		{"shieldRechargeRate", 10.903},
		{"shieldHitpointsMaximumFront", 1654.72},
		{"shieldHitpointsMaximumBack", 1654.72},
		{"currentHitpoints", 1284.84},
		{"maximumHitpoints", 1284.84},
		{"maximumArmorHitpoints", 642.42},
		{"currentArmorHitpoints", 642.42},
		{"efficiency", 1},
		{"energyMaintenance", 2931},
		{"mass", 43543.5},
		{"reverseEngineeringLevel", 8},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_gallofree_defender_2, "object/tangible/ship/components/shield_generator/shd_gallofree_defender_2.iff")
