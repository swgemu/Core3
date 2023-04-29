object_tangible_ship_components_armor_arm_mandal_elite_composite = object_tangible_ship_components_armor_shared_arm_mandal_elite_composite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_mandal_elite_composite",

	attributes = {
		{"currentHitpoints", 1144.39},
		{"maximumHitpoints", 1144.39},
		{"maximumArmorHitpoints", 1144.39},
		{"currentArmorHitpoints", 1144.39},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_mandal_elite_composite, "object/tangible/ship/components/armor/arm_mandal_elite_composite.iff")
