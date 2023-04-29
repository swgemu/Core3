object_tangible_ship_components_armor_arm_corellian_modified_heavy_durasteel = object_tangible_ship_components_armor_shared_arm_corellian_modified_heavy_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_corellian_modified_heavy_durasteel",

	attributes = {
		{"currentHitpoints", 1039.08},
		{"maximumHitpoints", 1039.08},
		{"maximumArmorHitpoints", 1039.08},
		{"currentArmorHitpoints", 1039.08},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 13492.4},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.433},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_corellian_modified_heavy_durasteel, "object/tangible/ship/components/armor/arm_corellian_modified_heavy_durasteel.iff")
