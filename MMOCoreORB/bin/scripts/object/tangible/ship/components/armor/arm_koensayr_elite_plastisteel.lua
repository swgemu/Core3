object_tangible_ship_components_armor_arm_koensayr_elite_plastisteel = object_tangible_ship_components_armor_shared_arm_koensayr_elite_plastisteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_koensayr_elite_plastisteel",

	attributes = {
		{"currentHitpoints", 1208.95},
		{"maximumHitpoints", 1208.95},
		{"maximumArmorHitpoints", 1208.95},
		{"currentArmorHitpoints", 1208.95},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 33731.1},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.3},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_koensayr_elite_plastisteel, "object/tangible/ship/components/armor/arm_koensayr_elite_plastisteel.iff")
