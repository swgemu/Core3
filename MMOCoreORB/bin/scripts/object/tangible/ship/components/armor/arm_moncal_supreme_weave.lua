object_tangible_ship_components_armor_arm_moncal_supreme_weave = object_tangible_ship_components_armor_shared_arm_moncal_supreme_weave:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_moncal_supreme_weave",

	attributes = {
		{"currentHitpoints", 1511.19},
		{"maximumHitpoints", 1511.19},
		{"maximumArmorHitpoints", 1511.19},
		{"currentArmorHitpoints", 1511.19},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 42342.3},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.4},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_moncal_supreme_weave, "object/tangible/ship/components/armor/arm_moncal_supreme_weave.iff")
