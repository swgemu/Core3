object_tangible_ship_components_armor_arm_rendili_tough_plate = object_tangible_ship_components_armor_shared_arm_rendili_tough_plate:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_rendili_tough_plate",

	attributes = {
		{"currentHitpoints", 208.5},
		{"maximumHitpoints", 208.5},
		{"maximumArmorHitpoints", 208.5},
		{"currentArmorHitpoints", 208.5},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 1545.07},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_rendili_tough_plate, "object/tangible/ship/components/armor/arm_rendili_tough_plate.iff")
