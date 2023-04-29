object_tangible_ship_components_armor_arm_mandal_enhanced_elite_composite = object_tangible_ship_components_armor_shared_arm_mandal_enhanced_elite_composite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_mandal_enhanced_elite_composite",

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
		{"maximumArmorHitpoints", 0.2},
		{"energyMaintenance", 0},
		{"mass", 0.4},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_mandal_enhanced_elite_composite, "object/tangible/ship/components/armor/arm_mandal_enhanced_elite_composite.iff")
