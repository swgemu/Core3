object_tangible_ship_components_armor_armor_trilon_unknown = object_tangible_ship_components_armor_shared_armor_trilon_unknown:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_trilon_unknown.iff",

	attributes = {
		{"currentHitpoints", 705.898},
		{"maximumHitpoints", 705.898},
		{"maximumArmorHitpoints", 705.898},
		{"currentArmorHitpoints", 705.898},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_armor_trilon_unknown, "object/tangible/ship/components/armor/armor_trilon_unknown.iff")
