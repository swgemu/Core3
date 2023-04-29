object_tangible_ship_components_armor_arm_koensayr_light_advanced_durasteel = object_tangible_ship_components_armor_shared_arm_koensayr_light_advanced_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_koensayr_light_advanced_durasteel",

	attributes = {
		{"currentHitpoints", 528.154},
		{"maximumHitpoints", 528.154},
		{"maximumArmorHitpoints", 528.154},
		{"currentArmorHitpoints", 528.154},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 4955.62},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.375},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_koensayr_light_advanced_durasteel, "object/tangible/ship/components/armor/arm_koensayr_light_advanced_durasteel.iff")
