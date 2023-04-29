object_tangible_ship_components_armor_armor_trilon_custom = object_tangible_ship_components_armor_shared_armor_trilon_custom:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_trilon_custom.iff",

	attributes = {
		{"currentHitpoints", 612.794},
		{"maximumHitpoints", 612.794},
		{"maximumArmorHitpoints", 612.794},
		{"currentArmorHitpoints", 612.794},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 5518.12},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.375},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_armor_trilon_custom, "object/tangible/ship/components/armor/armor_trilon_custom.iff")
