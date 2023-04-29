object_tangible_ship_components_armor_arm_corellian_elite_durasteel = object_tangible_ship_components_armor_shared_arm_corellian_elite_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_corellian_elite_durasteel",

	attributes = {
		{"currentHitpoints", 915.514},
		{"maximumHitpoints", 915.514},
		{"maximumArmorHitpoints", 915.514},
		{"currentArmorHitpoints", 915.514},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 27413.1},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.483},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_corellian_elite_durasteel, "object/tangible/ship/components/armor/arm_corellian_elite_durasteel.iff")
