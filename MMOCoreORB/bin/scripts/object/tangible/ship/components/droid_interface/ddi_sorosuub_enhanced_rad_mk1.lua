object_tangible_ship_components_droid_interface_ddi_sorosuub_enhanced_rad_mk1 = object_tangible_ship_components_droid_interface_shared_ddi_sorosuub_enhanced_rad_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "ddi_sorosuub_enhanced_rad_mk1",

	attributes = {
		{"commandSpeed", 29.25},
		{"currentHitpoints", 517.5},
		{"maximumHitpoints", 517.5},
		{"maximumArmorHitpointsMod", 0.05},
		{"maximumArmorHitpoints", 258.75},
		{"currentArmorHitpoints", 258.75},
		{"efficiency", 1},
		{"energyMaintenance", 500},
		{"mass", 2187.5},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"commandSpeed", 0.05},
		{"energyMaintenance", 0.05},
		{"mass", 0.05},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_droid_interface_ddi_sorosuub_enhanced_rad_mk1, "object/tangible/ship/components/droid_interface/ddi_sorosuub_enhanced_rad_mk1.iff")
