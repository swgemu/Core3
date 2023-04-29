object_tangible_ship_components_droid_interface_ddi_gallofree_level1 = object_tangible_ship_components_droid_interface_shared_ddi_gallofree_level1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "ddi_gallofree_level1",

	attributes = {
		{"commandSpeed", 24},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpointsMod", 0.05},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 500},
		{"mass", 3125},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"commandSpeed", 0.05},
		{"energyMaintenance", 0.05},
		{"mass", 0.05},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_droid_interface_ddi_gallofree_level1, "object/tangible/ship/components/droid_interface/ddi_gallofree_level1.iff")
