object_tangible_ship_components_armor_arm_moncal_elite_weave = object_tangible_ship_components_armor_shared_arm_moncal_elite_weave:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_moncal_elite_weave",

	attributes = {
		{"currentHitpoints", 1327.79},
		{"maximumHitpoints", 1327.79},
		{"maximumArmorHitpoints", 1327.79},
		{"currentArmorHitpoints", 1327.79},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 41496.3},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.483},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_moncal_elite_weave, "object/tangible/ship/components/armor/arm_moncal_elite_weave.iff")
