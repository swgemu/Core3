object_tangible_ship_components_armor_arm_koensayr_supreme_durasteel = object_tangible_ship_components_armor_shared_arm_koensayr_supreme_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_koensayr_supreme_durasteel",

	attributes = {
		{"currentHitpoints", 1026.62},
		{"maximumHitpoints", 1026.62},
		{"maximumArmorHitpoints", 1026.62},
		{"currentArmorHitpoints", 1026.62},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 13632.8},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.433},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_koensayr_supreme_durasteel, "object/tangible/ship/components/armor/arm_koensayr_supreme_durasteel.iff")
