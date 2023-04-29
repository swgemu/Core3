object_tangible_ship_components_armor_armor_subpro_reinforced_plasteel = object_tangible_ship_components_armor_shared_armor_subpro_reinforced_plasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_subpro_reinforced_plasteel.iff",

	attributes = {
		{"currentHitpoints", 871.792},
		{"maximumHitpoints", 871.792},
		{"maximumArmorHitpoints", 871.792},
		{"currentArmorHitpoints", 871.792},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 9645.68},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.3},
		{"energyMaintenance", 0},
		{"mass", 0.375},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_armor_subpro_reinforced_plasteel, "object/tangible/ship/components/armor/armor_subpro_reinforced_plasteel.iff")
