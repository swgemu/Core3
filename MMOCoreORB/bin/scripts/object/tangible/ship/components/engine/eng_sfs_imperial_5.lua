object_tangible_ship_components_engine_eng_sfs_imperial_5 = object_tangible_ship_components_engine_shared_eng_sfs_imperial_5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_sfs_imperial_5",

	attributes = {
		{"maxSpeed", 73.7625},
		{"maxPitch", 67},
		{"maxRoll", 67},
		{"maxYaw", 67},
		{"currentHitpoints", 1109.64},
		{"maximumHitpoints", 1109.64},
		{"maximumArmorHitpoints", 554.818},
		{"currentArmorHitpoints", 554.818},
		{"efficiency", 1},
		{"energyMaintenance", 1650},
		{"mass", 28255.5},
		{"reverseEngineeringLevel", 8},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_sfs_imperial_5, "object/tangible/ship/components/engine/eng_sfs_imperial_5.iff")
