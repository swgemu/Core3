object_tangible_ship_components_armor_arm_kse_supreme_durasteel = object_tangible_ship_components_armor_shared_arm_kse_supreme_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_kse_supreme_durasteel",

	attributes = {
		{"currentHitpoints", 1051.54},
		{"maximumHitpoints", 1051.54},
		{"maximumArmorHitpoints", 1051.54},
		{"currentArmorHitpoints", 1051.54},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 13773.2},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.39},
		{"energyMaintenance", 0},
		{"mass", 0.433},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_kse_supreme_durasteel, "object/tangible/ship/components/armor/arm_kse_supreme_durasteel.iff")
