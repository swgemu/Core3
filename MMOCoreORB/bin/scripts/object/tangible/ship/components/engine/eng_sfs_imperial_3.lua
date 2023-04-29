object_tangible_ship_components_engine_eng_sfs_imperial_3 = object_tangible_ship_components_engine_shared_eng_sfs_imperial_3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_sfs_imperial_3",

	attributes = {
		{"maxSpeed", 55.314},
		{"maxPitch", 48.032},
		{"maxRoll", 48.032},
		{"maxYaw", 48.032},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 1650},
		{"mass", 6187.5},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"maxSpeed", 0.1},
		{"maxPitch", 0.09},
		{"maxRoll", 0.09},
		{"maxYaw", 0.09},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.14},
		{"mass", 0.14},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_sfs_imperial_3, "object/tangible/ship/components/engine/eng_sfs_imperial_3.iff")
