object_tangible_ship_components_armor_arm_corellian_cheap_durasteel = object_tangible_ship_components_armor_shared_arm_corellian_cheap_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_corellian_cheap_durasteel",

	attributes = {
		{"currentHitpoints", 144.8},
		{"maximumHitpoints", 144.8},
		{"maximumArmorHitpoints", 144.8},
		{"currentArmorHitpoints", 144.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 900.9},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_corellian_cheap_durasteel, "object/tangible/ship/components/armor/arm_corellian_cheap_durasteel.iff")
