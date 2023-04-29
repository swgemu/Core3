object_tangible_ship_components_armor_armor_freitek_es4_durasteel = object_tangible_ship_components_armor_shared_armor_freitek_es4_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_freitek_es4_durasteel.iff",

	attributes = {
		{"currentHitpoints", 383.64},
		{"maximumHitpoints", 383.64},
		{"maximumArmorHitpoints", 383.64},
		{"currentArmorHitpoints", 383.64},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 2207.25},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.316},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_armor_freitek_es4_durasteel, "object/tangible/ship/components/armor/armor_freitek_es4_durasteel.iff")
