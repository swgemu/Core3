object_tangible_ship_components_armor_arm_corellian_enhanced_elite_plastisteel = object_tangible_ship_components_armor_shared_arm_corellian_enhanced_elite_plastisteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_corellian_enhanced_elite_plastisteel",

	attributes = {
		{"currentHitpoints", 1529.53},
		{"maximumHitpoints", 1529.53},
		{"maximumArmorHitpoints", 1529.53},
		{"currentArmorHitpoints", 1529.53},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 40650.3},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.483},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_corellian_enhanced_elite_plastisteel, "object/tangible/ship/components/armor/arm_corellian_enhanced_elite_plastisteel.iff")
