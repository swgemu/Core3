object_tangible_ship_components_armor_arm_sorosuub_enhanced_advanced_plastisteel = object_tangible_ship_components_armor_shared_arm_sorosuub_enhanced_advanced_plastisteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_sorosuub_enhanced_advanced_plastisteel",

	attributes = {
		{"currentHitpoints", 1208.95},
		{"maximumHitpoints", 1208.95},
		{"maximumArmorHitpoints", 1208.95},
		{"currentArmorHitpoints", 1208.95},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 34433.1},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.3},
		{"energyMaintenance", 0},
		{"mass", 0.483},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_sorosuub_enhanced_advanced_plastisteel, "object/tangible/ship/components/armor/arm_sorosuub_enhanced_advanced_plastisteel.iff")
