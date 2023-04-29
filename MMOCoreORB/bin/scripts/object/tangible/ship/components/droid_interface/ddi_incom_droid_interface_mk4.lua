object_tangible_ship_components_droid_interface_ddi_incom_droid_interface_mk4 = object_tangible_ship_components_droid_interface_shared_ddi_incom_droid_interface_mk4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "ddi_incom_droid_interface_mk4",

	attributes = {
		{"commandSpeed", 16.5},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpointsMod", 0.05},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 500},
		{"mass", 7800},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"commandSpeed", 0.05},
		{"energyMaintenance", 0.05},
		{"mass", 0.05},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_droid_interface_ddi_incom_droid_interface_mk4, "object/tangible/ship/components/droid_interface/ddi_incom_droid_interface_mk4.iff")
