object_tangible_ship_components_armor_arm_mandal_insulated_i7 = object_tangible_ship_components_armor_shared_arm_mandal_insulated_i7:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_mandal_insulated_i7",

	attributes = {
		{"currentHitpoints", 1026.62},
		{"maximumHitpoints", 1026.62},
		{"maximumArmorHitpoints", 1026.62},
		{"currentArmorHitpoints", 1026.62},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 13773.2},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.2},
		{"energyMaintenance", 0},
		{"mass", 0.433},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_mandal_insulated_i7, "object/tangible/ship/components/armor/arm_mandal_insulated_i7.iff")
