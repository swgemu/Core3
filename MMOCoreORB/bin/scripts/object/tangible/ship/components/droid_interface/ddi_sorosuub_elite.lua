object_tangible_ship_components_droid_interface_ddi_sorosuub_elite = object_tangible_ship_components_droid_interface_shared_ddi_sorosuub_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "ddi_sorosuub_elite",

	attributes = {
		{"commandSpeed", 10.125},
		{"currentHitpoints", 1650.57},
		{"maximumHitpoints", 1650.57},
		{"maximumArmorHitpointsMod", 0.05},
		{"maximumArmorHitpoints", 825.285},
		{"currentArmorHitpoints", 825.285},
		{"efficiency", 1},
		{"energyMaintenance", 500},
		{"mass", 23500},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"commandSpeed", 0.05},
		{"energyMaintenance", 0.05},
		{"mass", 0.05},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_droid_interface_ddi_sorosuub_elite, "object/tangible/ship/components/droid_interface/ddi_sorosuub_elite.iff")
