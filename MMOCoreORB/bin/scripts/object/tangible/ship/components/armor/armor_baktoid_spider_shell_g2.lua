object_tangible_ship_components_armor_armor_baktoid_spider_shell_g2 = object_tangible_ship_components_armor_shared_armor_baktoid_spider_shell_g2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_baktoid_spider_shell_g2.iff",

	attributes = {
		{"currentHitpoints", 211},
		{"maximumHitpoints", 211},
		{"maximumArmorHitpoints", 211},
		{"currentArmorHitpoints", 211},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 1545.07},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.39},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_armor_baktoid_spider_shell_g2, "object/tangible/ship/components/armor/armor_baktoid_spider_shell_g2.iff")
