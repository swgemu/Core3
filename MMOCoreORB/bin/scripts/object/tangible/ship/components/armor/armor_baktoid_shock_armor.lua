object_tangible_ship_components_armor_armor_baktoid_shock_armor = object_tangible_ship_components_armor_shared_armor_baktoid_shock_armor:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_baktoid_shock_armor.iff",

	attributes = {
		{"currentHitpoints", 206},
		{"maximumHitpoints", 206},
		{"maximumArmorHitpoints", 206},
		{"currentArmorHitpoints", 206},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 1513.57},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_armor_baktoid_shock_armor, "object/tangible/ship/components/armor/armor_baktoid_shock_armor.iff")
