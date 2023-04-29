object_tangible_ship_components_armor_arm_kse_elite_durasteel = object_tangible_ship_components_armor_shared_arm_kse_elite_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_kse_elite_durasteel",

	attributes = {
		{"currentHitpoints", 1283.28},
		{"maximumHitpoints", 1283.28},
		{"maximumArmorHitpoints", 1283.28},
		{"currentArmorHitpoints", 1283.28},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 24103.2},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.39},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_kse_elite_durasteel, "object/tangible/ship/components/armor/arm_kse_elite_durasteel.iff")
