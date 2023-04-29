object_tangible_ship_components_armor_arm_koensayr_b5_durasteel = object_tangible_ship_components_armor_shared_arm_koensayr_b5_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_koensayr_b5_durasteel",

	attributes = {
		{"currentHitpoints", 168.8},
		{"maximumHitpoints", 168.8},
		{"maximumArmorHitpoints", 168.8},
		{"currentArmorHitpoints", 168.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 882.9},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.39},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_koensayr_b5_durasteel, "object/tangible/ship/components/armor/arm_koensayr_b5_durasteel.iff")
