object_tangible_ship_components_engine_eng_sfs_advanced = object_tangible_ship_components_engine_shared_eng_sfs_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_sfs_advanced",

	attributes = {
		{"maxSpeed", 69.3945},
		{"maxPitch", 53.9695},
		{"maxRoll", 53.9695},
		{"maxYaw", 53.9695},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 1800},
		{"mass", 42120},
		{"reverseEngineeringLevel", 9},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_sfs_advanced, "object/tangible/ship/components/engine/eng_sfs_advanced.iff")
