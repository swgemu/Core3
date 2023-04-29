object_tangible_ship_components_armor_arm_kse_advanced_durasteel = object_tangible_ship_components_armor_shared_arm_kse_advanced_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_kse_advanced_durasteel",

	attributes = {
		{"currentHitpoints", 882.372},
		{"maximumHitpoints", 882.372},
		{"maximumArmorHitpoints", 882.372},
		{"currentArmorHitpoints", 882.372},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 9842.33},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.375},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_kse_advanced_durasteel, "object/tangible/ship/components/armor/arm_kse_advanced_durasteel.iff")
