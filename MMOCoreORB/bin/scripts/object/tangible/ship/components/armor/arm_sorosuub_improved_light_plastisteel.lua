object_tangible_ship_components_armor_arm_sorosuub_improved_light_plastisteel = object_tangible_ship_components_armor_shared_arm_sorosuub_improved_light_plastisteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_sorosuub_improved_light_plastisteel",

	attributes = {
		{"currentHitpoints", 206},
		{"maximumHitpoints", 206},
		{"maximumArmorHitpoints", 206},
		{"currentArmorHitpoints", 206},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 1513.57},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_sorosuub_improved_light_plastisteel, "object/tangible/ship/components/armor/arm_sorosuub_improved_light_plastisteel.iff")
