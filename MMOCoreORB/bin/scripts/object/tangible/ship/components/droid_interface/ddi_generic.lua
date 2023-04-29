object_tangible_ship_components_droid_interface_ddi_generic = object_tangible_ship_components_droid_interface_shared_ddi_generic:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "ddi_z95_basic",

	attributes = {
		{"commandSpeed", 34.5},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpointsMod", 0.05},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 500},
		{"mass", 500},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"commandSpeed", 0.05},
		{"energyMaintenance", 0.05},
		{"mass", 0.05},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_droid_interface_ddi_generic, "object/tangible/ship/components/droid_interface/ddi_generic.iff")
