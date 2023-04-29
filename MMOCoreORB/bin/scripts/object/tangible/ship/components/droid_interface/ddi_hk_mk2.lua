object_tangible_ship_components_droid_interface_ddi_hk_mk2 = object_tangible_ship_components_droid_interface_shared_ddi_hk_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "ddi_hk_mk2",

	attributes = {
		{"commandSpeed", 19.125},
		{"currentHitpoints", 952.2},
		{"maximumHitpoints", 952.2},
		{"maximumArmorHitpointsMod", 0.05},
		{"maximumArmorHitpoints", 476.1},
		{"currentArmorHitpoints", 476.1},
		{"efficiency", 1},
		{"energyMaintenance", 500},
		{"mass", 5462.5},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"commandSpeed", 0.05},
		{"energyMaintenance", 0.05},
		{"mass", 0.05},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_droid_interface_ddi_hk_mk2, "object/tangible/ship/components/droid_interface/ddi_hk_mk2.iff")
