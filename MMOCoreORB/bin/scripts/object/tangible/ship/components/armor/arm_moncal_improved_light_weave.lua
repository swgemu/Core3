object_tangible_ship_components_armor_arm_moncal_improved_light_weave = object_tangible_ship_components_armor_shared_arm_moncal_improved_light_weave:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_moncal_improved_light_weave",

	attributes = {
		{"currentHitpoints", 206},
		{"maximumHitpoints", 206},
		{"maximumArmorHitpoints", 206},
		{"currentArmorHitpoints", 206},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 1214.32},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.25},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_moncal_improved_light_weave, "object/tangible/ship/components/armor/arm_moncal_improved_light_weave.iff")
