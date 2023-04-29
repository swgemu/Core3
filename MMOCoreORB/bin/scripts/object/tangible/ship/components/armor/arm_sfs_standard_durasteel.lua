object_tangible_ship_components_armor_arm_sfs_standard_durasteel = object_tangible_ship_components_armor_shared_arm_sfs_standard_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_sfs_standard_durasteel",

	attributes = {
		{"currentHitpoints", 379.04},
		{"maximumHitpoints", 379.04},
		{"maximumArmorHitpoints", 379.04},
		{"currentArmorHitpoints", 379.04},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 2162.25},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.318},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_sfs_standard_durasteel, "object/tangible/ship/components/armor/arm_sfs_standard_durasteel.iff")
