object_tangible_ship_components_droid_interface_ddi_incom_advanced_droid_interface = object_tangible_ship_components_droid_interface_shared_ddi_incom_advanced_droid_interface:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "ddi_incom_advanced_droid_interface",

	attributes = {
		{"commandSpeed", 13.5},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpointsMod", 0.05},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 500},
		{"mass", 19500},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"commandSpeed", 0.05},
		{"energyMaintenance", 0.05},
		{"mass", 0.05},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_droid_interface_ddi_incom_advanced_droid_interface, "object/tangible/ship/components/droid_interface/ddi_incom_advanced_droid_interface.iff")
