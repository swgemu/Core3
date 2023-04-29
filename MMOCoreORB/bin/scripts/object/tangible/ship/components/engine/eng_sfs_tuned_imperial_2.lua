object_tangible_ship_components_engine_eng_sfs_tuned_imperial_2 = object_tangible_ship_components_engine_shared_eng_sfs_tuned_imperial_2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_sfs_tuned_imperial_2",

	attributes = {
		{"maxSpeed", 58.8},
		{"maxPitch", 59.625},
		{"maxRoll", 59.625},
		{"maxYaw", 59.625},
		{"currentHitpoints", 474.375},
		{"maximumHitpoints", 474.375},
		{"maximumArmorHitpoints", 237.188},
		{"currentArmorHitpoints", 237.188},
		{"efficiency", 1},
		{"energyMaintenance", 1575},
		{"mass", 4528.12},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maxSpeed", 0.1},
		{"maxPitch", 0.07},
		{"maxRoll", 0.07},
		{"maxYaw", 0.07},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.14},
		{"mass", 0.14},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_sfs_tuned_imperial_2, "object/tangible/ship/components/engine/eng_sfs_tuned_imperial_2.iff")
