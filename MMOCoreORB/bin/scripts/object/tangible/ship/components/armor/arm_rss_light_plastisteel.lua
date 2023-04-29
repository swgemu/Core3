object_tangible_ship_components_armor_arm_rss_light_plastisteel = object_tangible_ship_components_armor_shared_arm_rss_light_plastisteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_rss_light_plastisteel",

	attributes = {
		{"currentHitpoints", 164.8},
		{"maximumHitpoints", 164.8},
		{"maximumArmorHitpoints", 164.8},
		{"currentArmorHitpoints", 164.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 882.9},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.3},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_rss_light_plastisteel, "object/tangible/ship/components/armor/arm_rss_light_plastisteel.iff")
