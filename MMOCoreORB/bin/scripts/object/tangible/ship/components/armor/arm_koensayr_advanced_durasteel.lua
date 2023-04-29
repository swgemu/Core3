object_tangible_ship_components_armor_arm_koensayr_advanced_durasteel = object_tangible_ship_components_armor_shared_arm_koensayr_advanced_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_koensayr_advanced_durasteel",

	attributes = {
		{"currentHitpoints", 871.792},
		{"maximumHitpoints", 871.792},
		{"maximumArmorHitpoints", 871.792},
		{"currentArmorHitpoints", 871.792},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 9449.03},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.375},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_koensayr_advanced_durasteel, "object/tangible/ship/components/armor/arm_koensayr_advanced_durasteel.iff")
