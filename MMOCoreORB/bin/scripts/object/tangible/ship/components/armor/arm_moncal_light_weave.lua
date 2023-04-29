object_tangible_ship_components_armor_arm_moncal_light_weave = object_tangible_ship_components_armor_shared_arm_moncal_light_weave:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_moncal_light_weave",

	attributes = {
		{"currentHitpoints", 124.8},
		{"maximumHitpoints", 124.8},
		{"maximumArmorHitpoints", 124.8},
		{"currentArmorHitpoints", 124.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 702.9},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.14},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_moncal_light_weave, "object/tangible/ship/components/armor/arm_moncal_light_weave.iff")
