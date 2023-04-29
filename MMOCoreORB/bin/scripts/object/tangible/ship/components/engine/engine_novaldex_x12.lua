object_tangible_ship_components_engine_engine_novaldex_x12 = object_tangible_ship_components_engine_shared_engine_novaldex_x12:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_novaldex_x12",

	attributes = {
		{"maxSpeed", 82.6125},
		{"maxPitch", 71.0125},
		{"maxRoll", 71.0125},
		{"maxYaw", 71.0125},
		{"currentHitpoints", 1306.7},
		{"maximumHitpoints", 1306.7},
		{"maximumArmorHitpoints", 653.351},
		{"currentArmorHitpoints", 653.351},
		{"efficiency", 1},
		{"energyMaintenance", 1725},
		{"mass", 50760},
		{"reverseEngineeringLevel", 10},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_engine_novaldex_x12, "object/tangible/ship/components/engine/engine_novaldex_x12.iff")
