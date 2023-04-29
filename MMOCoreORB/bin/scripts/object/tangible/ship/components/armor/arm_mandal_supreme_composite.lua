object_tangible_ship_components_armor_arm_mandal_supreme_composite = object_tangible_ship_components_armor_shared_arm_mandal_supreme_composite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_mandal_supreme_composite",

	attributes = {
		{"currentHitpoints", 1062.23},
		{"maximumHitpoints", 1062.23},
		{"maximumArmorHitpoints", 1062.23},
		{"currentArmorHitpoints", 1062.23},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 34433.1},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.483},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_mandal_supreme_composite, "object/tangible/ship/components/armor/arm_mandal_supreme_composite.iff")
