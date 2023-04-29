object_tangible_ship_components_engine_eng_sfs_imperial_4 = object_tangible_ship_components_engine_shared_eng_sfs_imperial_4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_sfs_imperial_4",

	attributes = {
		{"maxSpeed", 61.9605},
		{"maxPitch", 50.92},
		{"maxRoll", 50.92},
		{"maxYaw", 50.92},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 1725},
		{"mass", 16146},
		{"reverseEngineeringLevel", 7},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_sfs_imperial_4, "object/tangible/ship/components/engine/eng_sfs_imperial_4.iff")
