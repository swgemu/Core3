object_tangible_ship_components_droid_interface_ddi_kse_improved_manager_mk1 = object_tangible_ship_components_droid_interface_shared_ddi_kse_improved_manager_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "ddi_kse_improved_manager_mk1",

	attributes = {
		{"commandSpeed", 33.75},
		{"currentHitpoints", 225},
		{"maximumHitpoints", 225},
		{"maximumArmorHitpointsMod", 0.05},
		{"maximumArmorHitpoints", 112.5},
		{"currentArmorHitpoints", 112.5},
		{"efficiency", 1},
		{"energyMaintenance", 500},
		{"mass", 875},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"commandSpeed", 0.05},
		{"energyMaintenance", 0.05},
		{"mass", 0.05},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_droid_interface_ddi_kse_improved_manager_mk1, "object/tangible/ship/components/droid_interface/ddi_kse_improved_manager_mk1.iff")
