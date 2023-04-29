object_tangible_ship_components_armor_arm_corellian_advanced_durasteel = object_tangible_ship_components_armor_shared_arm_corellian_advanced_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_corellian_advanced_durasteel",

	attributes = {
		{"currentHitpoints", 902.032},
		{"maximumHitpoints", 902.032},
		{"maximumArmorHitpoints", 902.032},
		{"currentArmorHitpoints", 902.032},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 13773.2},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.433},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_corellian_advanced_durasteel, "object/tangible/ship/components/armor/arm_corellian_advanced_durasteel.iff")
