object_tangible_ship_components_armor_arm_kessel_rebel_mandal_corrugated_plastisteel = object_tangible_ship_components_armor_shared_arm_kessel_rebel_mandal_corrugated_plastisteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_kessel_rebel_mandal_corrugated_plastisteel",

	attributes = {
		{"currentHitpoints", 1540.53},
		{"maximumHitpoints", 1540.53},
		{"maximumArmorHitpoints", 1540.53},
		{"currentArmorHitpoints", 1540.53},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 42120},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.25},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_kessel_rebel_mandal_corrugated_plastisteel, "object/tangible/ship/components/armor/arm_kessel_rebel_mandal_corrugated_plastisteel.iff")
