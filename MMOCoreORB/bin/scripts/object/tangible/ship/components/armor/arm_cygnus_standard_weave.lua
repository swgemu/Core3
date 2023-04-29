object_tangible_ship_components_armor_arm_cygnus_standard_weave = object_tangible_ship_components_armor_shared_arm_cygnus_standard_weave:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_cygnus_standard_weave",

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
		{"mass", 0.318},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_cygnus_standard_weave, "object/tangible/ship/components/armor/arm_cygnus_standard_weave.iff")
