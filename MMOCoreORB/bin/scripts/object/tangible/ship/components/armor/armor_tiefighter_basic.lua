object_tangible_ship_components_armor_armor_tiefighter_basic = object_tangible_ship_components_armor_shared_armor_tiefighter_basic:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_tiefighter_basic",

	attributes = {
		{"currentHitpoints", 144.8},
		{"maximumHitpoints", 144.8},
		{"maximumArmorHitpoints", 144.8},
		{"currentArmorHitpoints", 144.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 792.9},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_armor_tiefighter_basic, "object/tangible/ship/components/armor/armor_tiefighter_basic.iff")
