object_tangible_ship_components_armor_arm_corellian_reinforced_light_durasteel = object_tangible_ship_components_armor_shared_arm_corellian_reinforced_light_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_corellian_reinforced_light_durasteel",

	attributes = {
		{"currentHitpoints", 287.04},
		{"maximumHitpoints", 287.04},
		{"maximumArmorHitpoints", 287.04},
		{"currentArmorHitpoints", 287.04},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 1757.25},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.318},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_corellian_reinforced_light_durasteel, "object/tangible/ship/components/armor/arm_corellian_reinforced_light_durasteel.iff")
