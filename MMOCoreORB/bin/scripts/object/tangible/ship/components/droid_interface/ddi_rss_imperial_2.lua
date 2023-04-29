object_tangible_ship_components_droid_interface_ddi_rss_imperial_2 = object_tangible_ship_components_droid_interface_shared_ddi_rss_imperial_2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "ddi_rss_imperial_2",

	attributes = {
		{"commandSpeed", 30},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpointsMod", 0.05},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 500},
		{"mass", 1250},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"commandSpeed", 0.05},
		{"energyMaintenance", 0.05},
		{"mass", 0.05},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_droid_interface_ddi_rss_imperial_2, "object/tangible/ship/components/droid_interface/ddi_rss_imperial_2.iff")
