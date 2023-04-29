object_tangible_ship_components_armor_arm_subpro_elite_plastisteel = object_tangible_ship_components_armor_shared_arm_subpro_elite_plastisteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_subpro_elite_plastisteel",

	attributes = {
		{"currentHitpoints", 1511.19},
		{"maximumHitpoints", 1511.19},
		{"maximumArmorHitpoints", 1511.19},
		{"currentArmorHitpoints", 1511.19},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 41496.3},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.3},
		{"energyMaintenance", 0},
		{"mass", 0.483},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_subpro_elite_plastisteel, "object/tangible/ship/components/armor/arm_subpro_elite_plastisteel.iff")
