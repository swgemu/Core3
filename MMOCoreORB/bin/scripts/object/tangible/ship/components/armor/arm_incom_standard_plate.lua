object_tangible_ship_components_armor_arm_incom_standard_plate = object_tangible_ship_components_armor_shared_arm_incom_standard_plate:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_incom_standard_plate",

	attributes = {
		{"currentHitpoints", 379.04},
		{"maximumHitpoints", 379.04},
		{"maximumArmorHitpoints", 379.04},
		{"currentArmorHitpoints", 379.04},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 2207.25},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.2},
		{"energyMaintenance", 0},
		{"mass", 0.318},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_incom_standard_plate, "object/tangible/ship/components/armor/arm_incom_standard_plate.iff")
