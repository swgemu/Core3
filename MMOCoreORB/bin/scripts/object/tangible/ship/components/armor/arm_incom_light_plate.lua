object_tangible_ship_components_armor_arm_incom_light_plate = object_tangible_ship_components_armor_shared_arm_incom_light_plate:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_incom_light_plate",

	attributes = {
		{"currentHitpoints", 164.8},
		{"maximumHitpoints", 164.8},
		{"maximumArmorHitpoints", 164.8},
		{"currentArmorHitpoints", 164.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 864.9},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_incom_light_plate, "object/tangible/ship/components/armor/arm_incom_light_plate.iff")
