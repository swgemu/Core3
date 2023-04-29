object_tangible_ship_components_armor_armor_alderaan_royal_plate = object_tangible_ship_components_armor_shared_armor_alderaan_royal_plate:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_alderaan_royal_plate.iff",

	attributes = {
		{"currentHitpoints", 479.55},
		{"maximumHitpoints", 479.55},
		{"maximumArmorHitpoints", 479.55},
		{"currentArmorHitpoints", 479.55},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 3862.69},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.316},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_armor_alderaan_royal_plate, "object/tangible/ship/components/armor/armor_alderaan_royal_plate.iff")
