object_tangible_ship_components_armor_arm_kessel_imperial_rendili_crystalline_durasteel = object_tangible_ship_components_armor_shared_arm_kessel_imperial_rendili_crystalline_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_kessel_imperial_rendili_crystalline_durasteel",

	attributes = {
		{"currentHitpoints", 1540.53},
		{"maximumHitpoints", 1540.53},
		{"maximumArmorHitpoints", 1540.53},
		{"currentArmorHitpoints", 1540.53},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 42120},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.483},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_kessel_imperial_rendili_crystalline_durasteel, "object/tangible/ship/components/armor/arm_kessel_imperial_rendili_crystalline_durasteel.iff")
