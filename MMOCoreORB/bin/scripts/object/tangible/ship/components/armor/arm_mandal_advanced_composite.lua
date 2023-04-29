object_tangible_ship_components_armor_arm_mandal_advanced_composite = object_tangible_ship_components_armor_shared_arm_mandal_advanced_composite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_mandal_advanced_composite",

	attributes = {
		{"currentHitpoints", 777.442},
		{"maximumHitpoints", 777.442},
		{"maximumArmorHitpoints", 777.442},
		{"currentArmorHitpoints", 777.442},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 13773.2},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.433},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_mandal_advanced_composite, "object/tangible/ship/components/armor/arm_mandal_advanced_composite.iff")
