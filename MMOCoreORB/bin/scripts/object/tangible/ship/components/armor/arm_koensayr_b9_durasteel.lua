object_tangible_ship_components_armor_arm_koensayr_b9_durasteel = object_tangible_ship_components_armor_shared_arm_koensayr_b9_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_koensayr_b9_durasteel",

	attributes = {
		{"currentHitpoints", 164.8},
		{"maximumHitpoints", 164.8},
		{"maximumArmorHitpoints", 164.8},
		{"currentArmorHitpoints", 164.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 873.9},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.25},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_koensayr_b9_durasteel, "object/tangible/ship/components/armor/arm_koensayr_b9_durasteel.iff")
