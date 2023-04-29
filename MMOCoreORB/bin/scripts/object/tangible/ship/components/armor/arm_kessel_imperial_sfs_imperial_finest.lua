object_tangible_ship_components_armor_arm_kessel_imperial_sfs_imperial_finest = object_tangible_ship_components_armor_shared_arm_kessel_imperial_sfs_imperial_finest:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_kessel_imperial_sfs_imperial_finest",

	attributes = {
		{"currentHitpoints", 1467.17},
		{"maximumHitpoints", 1467.17},
		{"maximumArmorHitpoints", 1467.17},
		{"currentArmorHitpoints", 1467.17},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 38610},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.1},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_kessel_imperial_sfs_imperial_finest, "object/tangible/ship/components/armor/arm_kessel_imperial_sfs_imperial_finest.iff")
