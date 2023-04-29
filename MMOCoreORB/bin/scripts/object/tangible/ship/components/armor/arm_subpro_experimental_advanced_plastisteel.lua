object_tangible_ship_components_armor_arm_subpro_experimental_advanced_plastisteel = object_tangible_ship_components_armor_shared_arm_subpro_experimental_advanced_plastisteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_subpro_experimental_advanced_plastisteel",

	attributes = {
		{"currentHitpoints", 1283.28},
		{"maximumHitpoints", 1283.28},
		{"maximumArmorHitpoints", 1283.28},
		{"currentArmorHitpoints", 1283.28},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 23857.5},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.433},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_subpro_experimental_advanced_plastisteel, "object/tangible/ship/components/armor/arm_subpro_experimental_advanced_plastisteel.iff")
