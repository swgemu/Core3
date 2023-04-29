object_tangible_ship_components_armor_arm_mandal_reinforced_advanced_composite = object_tangible_ship_components_armor_shared_arm_mandal_reinforced_advanced_composite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_mandal_reinforced_advanced_composite",

	attributes = {
		{"currentHitpoints", 1283.28},
		{"maximumHitpoints", 1283.28},
		{"maximumArmorHitpoints", 1283.28},
		{"currentArmorHitpoints", 1283.28},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 21646.2},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.433},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_mandal_reinforced_advanced_composite, "object/tangible/ship/components/armor/arm_mandal_reinforced_advanced_composite.iff")
