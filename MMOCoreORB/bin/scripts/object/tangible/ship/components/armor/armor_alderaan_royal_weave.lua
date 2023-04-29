object_tangible_ship_components_armor_armor_alderaan_royal_weave = object_tangible_ship_components_armor_shared_armor_alderaan_royal_weave:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_alderaan_royal_weave.iff",

	attributes = {
		{"currentHitpoints", 416.3},
		{"maximumHitpoints", 416.3},
		{"maximumArmorHitpoints", 416.3},
		{"currentArmorHitpoints", 416.3},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 3468.94},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.315},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_armor_alderaan_royal_weave, "object/tangible/ship/components/armor/armor_alderaan_royal_weave.iff")
