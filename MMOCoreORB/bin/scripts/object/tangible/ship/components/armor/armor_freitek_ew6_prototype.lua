object_tangible_ship_components_armor_armor_freitek_ew6_prototype = object_tangible_ship_components_armor_shared_armor_freitek_ew6_prototype:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_freitek_ew6_prototype.iff",

	attributes = {
		{"currentHitpoints", 379.04},
		{"maximumHitpoints", 379.04},
		{"maximumArmorHitpoints", 379.04},
		{"currentArmorHitpoints", 379.04},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 2207.25},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.317},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_armor_freitek_ew6_prototype, "object/tangible/ship/components/armor/armor_freitek_ew6_prototype.iff")
