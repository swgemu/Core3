object_tangible_ship_components_armor_armor_baktoid_mtt_prototype = object_tangible_ship_components_armor_shared_armor_baktoid_mtt_prototype:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_baktoid_mtt_prototype.iff",

	attributes = {
		{"currentHitpoints", 206},
		{"maximumHitpoints", 206},
		{"maximumArmorHitpoints", 206},
		{"currentArmorHitpoints", 206},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 1529.32},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.25},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_armor_baktoid_mtt_prototype, "object/tangible/ship/components/armor/armor_baktoid_mtt_prototype.iff")
