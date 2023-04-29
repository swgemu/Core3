object_tangible_ship_components_engine_engine_kuat_f31 = object_tangible_ship_components_engine_shared_engine_kuat_f31:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_kuat_f31",

	attributes = {
		{"maxSpeed", 59.01},
		{"maxPitch", 56.28},
		{"maxRoll", 56.28},
		{"maxYaw", 56.28},
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
		{"maxPitch", 0.06},
		{"maxRoll", 0.06},
		{"maxYaw", 0.06},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.14},
		{"mass", 0.14},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_engine_kuat_f31, "object/tangible/ship/components/engine/engine_kuat_f31.iff")
