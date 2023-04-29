object_tangible_ship_components_armor_arm_gallofree_mk2 = object_tangible_ship_components_armor_shared_arm_gallofree_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_gallofree_mk2",

	attributes = {
		{"currentHitpoints", 379.04},
		{"maximumHitpoints", 379.04},
		{"maximumArmorHitpoints", 379.04},
		{"currentArmorHitpoints", 379.04},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 2207.25},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.3},
		{"energyMaintenance", 0},
		{"mass", 0.318},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_gallofree_mk2, "object/tangible/ship/components/armor/arm_gallofree_mk2.iff")
