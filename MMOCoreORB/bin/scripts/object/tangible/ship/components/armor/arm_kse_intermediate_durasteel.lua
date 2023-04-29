object_tangible_ship_components_armor_arm_kse_intermediate_durasteel = object_tangible_ship_components_armor_shared_arm_kse_intermediate_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_kse_intermediate_durasteel",

	attributes = {
		{"currentHitpoints", 206},
		{"maximumHitpoints", 206},
		{"maximumArmorHitpoints", 206},
		{"currentArmorHitpoints", 206},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 1545.07},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.2},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_kse_intermediate_durasteel, "object/tangible/ship/components/armor/arm_kse_intermediate_durasteel.iff")
