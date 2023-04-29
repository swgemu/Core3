object_tangible_ship_components_armor_arm_corellian_reinforced_supreme_durasteel = object_tangible_ship_components_armor_shared_arm_corellian_reinforced_supreme_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_corellian_reinforced_supreme_durasteel",

	attributes = {
		{"currentHitpoints", 1208.95},
		{"maximumHitpoints", 1208.95},
		{"maximumArmorHitpoints", 1208.95},
		{"currentArmorHitpoints", 1208.95},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 35135.1},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.483},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_corellian_reinforced_supreme_durasteel, "object/tangible/ship/components/armor/arm_corellian_reinforced_supreme_durasteel.iff")
