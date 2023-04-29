object_tangible_ship_components_armor_arm_koensayr_reinforced_b5_durasteel = object_tangible_ship_components_armor_shared_arm_koensayr_reinforced_b5_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_koensayr_reinforced_b5_durasteel",

	attributes = {
		{"currentHitpoints", 206},
		{"maximumHitpoints", 206},
		{"maximumArmorHitpoints", 206},
		{"currentArmorHitpoints", 206},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 1513.57},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_koensayr_reinforced_b5_durasteel, "object/tangible/ship/components/armor/arm_koensayr_reinforced_b5_durasteel.iff")
