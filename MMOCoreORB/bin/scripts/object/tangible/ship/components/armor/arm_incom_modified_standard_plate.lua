object_tangible_ship_components_armor_arm_incom_modified_standard_plate = object_tangible_ship_components_armor_shared_arm_incom_modified_standard_plate:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_incom_modified_standard_plate",

	attributes = {
		{"currentHitpoints", 473.8},
		{"maximumHitpoints", 473.8},
		{"maximumArmorHitpoints", 473.8},
		{"currentArmorHitpoints", 473.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 3862.69},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.2},
		{"energyMaintenance", 0},
		{"mass", 0.318},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_incom_modified_standard_plate, "object/tangible/ship/components/armor/arm_incom_modified_standard_plate.iff")
