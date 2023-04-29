object_tangible_ship_components_armor_arm_moncal_advanced_weave = object_tangible_ship_components_armor_shared_arm_moncal_advanced_weave:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_moncal_advanced_weave",

	attributes = {
		{"currentHitpoints", 1547.86},
		{"maximumHitpoints", 1547.86},
		{"maximumArmorHitpoints", 1547.86},
		{"currentArmorHitpoints", 1547.86},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 33036.3},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.39},
		{"energyMaintenance", 0},
		{"mass", 0.483},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_moncal_advanced_weave, "object/tangible/ship/components/armor/arm_moncal_advanced_weave.iff")
