object_tangible_ship_components_armor_arm_corellian_special_standard_durasteel = object_tangible_ship_components_armor_shared_arm_corellian_special_standard_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_corellian_special_standard_durasteel",

	attributes = {
		{"currentHitpoints", 892.952},
		{"maximumHitpoints", 892.952},
		{"maximumArmorHitpoints", 892.952},
		{"currentArmorHitpoints", 892.952},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 9645.68},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.39},
		{"energyMaintenance", 0},
		{"mass", 0.375},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_corellian_special_standard_durasteel, "object/tangible/ship/components/armor/arm_corellian_special_standard_durasteel.iff")
