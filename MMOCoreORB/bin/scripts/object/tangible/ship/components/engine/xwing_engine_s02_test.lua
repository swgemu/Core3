object_tangible_ship_components_engine_xwing_engine_s02_test = object_tangible_ship_components_engine_shared_xwing_engine_s02_test:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "xwing_engine_s02_test",

	attributes = {
		{"maxSpeed", 42},
		{"maxPitch", 45},
		{"maxRoll", 45},
		{"maxYaw", 45},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 1500},
		{"mass", 900},
		{"reverseEngineeringLevel", 1},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_xwing_engine_s02_test, "object/tangible/ship/components/engine/xwing_engine_s02_test.iff")
