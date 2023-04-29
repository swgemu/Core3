object_tangible_ship_components_armor_arm_sorosuub_modified_elite_plastisteel = object_tangible_ship_components_armor_shared_arm_sorosuub_modified_elite_plastisteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_sorosuub_modified_elite_plastisteel",

	attributes = {
		{"currentHitpoints", 1511.19},
		{"maximumHitpoints", 1511.19},
		{"maximumArmorHitpoints", 1511.19},
		{"currentArmorHitpoints", 1511.19},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 41073.3},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.483},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_sorosuub_modified_elite_plastisteel, "object/tangible/ship/components/armor/arm_sorosuub_modified_elite_plastisteel.iff")
