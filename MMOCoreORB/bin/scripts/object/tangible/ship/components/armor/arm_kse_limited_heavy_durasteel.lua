object_tangible_ship_components_armor_arm_kse_limited_heavy_durasteel = object_tangible_ship_components_armor_shared_arm_kse_limited_heavy_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_kse_limited_heavy_durasteel",

	attributes = {
		{"currentHitpoints", 765.992},
		{"maximumHitpoints", 765.992},
		{"maximumArmorHitpoints", 765.992},
		{"currentArmorHitpoints", 765.992},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 7679.18},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.375},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_kse_limited_heavy_durasteel, "object/tangible/ship/components/armor/arm_kse_limited_heavy_durasteel.iff")
