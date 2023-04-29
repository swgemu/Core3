object_tangible_ship_components_armor_arm_sfs_light_durasteel = object_tangible_ship_components_armor_shared_arm_sfs_light_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_sfs_light_durasteel",

	attributes = {
		{"currentHitpoints", 164.8},
		{"maximumHitpoints", 164.8},
		{"maximumArmorHitpoints", 164.8},
		{"currentArmorHitpoints", 164.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 882.9},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.2},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_sfs_light_durasteel, "object/tangible/ship/components/armor/arm_sfs_light_durasteel.iff")
