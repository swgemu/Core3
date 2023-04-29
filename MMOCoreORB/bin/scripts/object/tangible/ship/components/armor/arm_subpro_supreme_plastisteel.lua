object_tangible_ship_components_armor_arm_subpro_supreme_plastisteel = object_tangible_ship_components_armor_shared_arm_subpro_supreme_plastisteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_subpro_supreme_plastisteel",

	attributes = {
		{"currentHitpoints", 1238.29},
		{"maximumHitpoints", 1238.29},
		{"maximumArmorHitpoints", 1238.29},
		{"currentArmorHitpoints", 1238.29},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 34433.1},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.39},
		{"energyMaintenance", 0},
		{"mass", 0.483},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_subpro_supreme_plastisteel, "object/tangible/ship/components/armor/arm_subpro_supreme_plastisteel.iff")
