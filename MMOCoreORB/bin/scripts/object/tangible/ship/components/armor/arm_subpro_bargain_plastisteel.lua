object_tangible_ship_components_armor_arm_subpro_bargain_plastisteel = object_tangible_ship_components_armor_shared_arm_subpro_bargain_plastisteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_subpro_bargain_plastisteel",

	attributes = {
		{"currentHitpoints", 124.8},
		{"maximumHitpoints", 124.8},
		{"maximumArmorHitpoints", 124.8},
		{"currentArmorHitpoints", 124.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 882.9},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.4},
		{"energyMaintenance", 0},
		{"mass", 0.14},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_subpro_bargain_plastisteel, "object/tangible/ship/components/armor/arm_subpro_bargain_plastisteel.iff")
