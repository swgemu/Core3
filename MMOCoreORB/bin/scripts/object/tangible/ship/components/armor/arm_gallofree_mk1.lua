object_tangible_ship_components_armor_arm_gallofree_mk1 = object_tangible_ship_components_armor_shared_arm_gallofree_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_gallofree_mk1",

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

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_gallofree_mk1, "object/tangible/ship/components/armor/arm_gallofree_mk1.iff")
