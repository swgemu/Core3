object_tangible_ship_components_armor_arm_generic = object_tangible_ship_components_armor_shared_arm_generic:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "armor_z95_basic",

	attributes = {
		{"currentHitpoints", 164.8},
		{"maximumHitpoints", 164.8},
		{"maximumArmorHitpoints", 164.8},
		{"currentArmorHitpoints", 164.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 882.9},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_generic, "object/tangible/ship/components/armor/arm_generic.iff")
