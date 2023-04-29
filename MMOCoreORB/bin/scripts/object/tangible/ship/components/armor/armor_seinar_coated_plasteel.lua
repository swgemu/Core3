object_tangible_ship_components_armor_armor_seinar_coated_plasteel = object_tangible_ship_components_armor_shared_armor_seinar_coated_plasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_seinar_coated_plasteel.iff",

	attributes = {
		{"currentHitpoints", 166.8},
		{"maximumHitpoints", 166.8},
		{"maximumArmorHitpoints", 166.8},
		{"currentArmorHitpoints", 166.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 882.9},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_armor_seinar_coated_plasteel, "object/tangible/ship/components/armor/armor_seinar_coated_plasteel.iff")
