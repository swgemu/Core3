object_tangible_ship_components_armor_arm_koensayr_heavy_durasteel = object_tangible_ship_components_armor_shared_arm_koensayr_heavy_durasteel:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_koensayr_heavy_durasteel",

	attributes = {
		{"currentHitpoints", 358.8},
		{"maximumHitpoints", 358.8},
		{"maximumArmorHitpoints", 358.8},
		{"currentArmorHitpoints", 358.8},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 3075.19},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.318},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_koensayr_heavy_durasteel, "object/tangible/ship/components/armor/arm_koensayr_heavy_durasteel.iff")
