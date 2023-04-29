object_tangible_ship_components_armor_armor_subpro_light_plasteel = object_tangible_ship_components_armor_shared_armor_subpro_light_plasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_subpro_light_plasteel.iff",

	attributes = {
		{"currentHitpoints", 697.434},
		{"maximumHitpoints", 697.434},
		{"maximumArmorHitpoints", 697.434},
		{"currentArmorHitpoints", 697.434},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 4955.62},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.375},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_armor_subpro_light_plasteel, "object/tangible/ship/components/armor/armor_subpro_light_plasteel.iff")
