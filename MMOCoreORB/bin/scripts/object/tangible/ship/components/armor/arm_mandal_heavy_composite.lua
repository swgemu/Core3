object_tangible_ship_components_armor_arm_mandal_heavy_composite = object_tangible_ship_components_armor_shared_arm_mandal_heavy_composite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_mandal_heavy_composite",

	attributes = {
		{"currentHitpoints", 714.362},
		{"maximumHitpoints", 714.362},
		{"maximumArmorHitpoints", 714.362},
		{"currentArmorHitpoints", 714.362},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 5518.12},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.39},
		{"energyMaintenance", 0},
		{"mass", 0.375},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_mandal_heavy_composite, "object/tangible/ship/components/armor/arm_mandal_heavy_composite.iff")
