object_tangible_ship_components_engine_engine_incom_e16 = object_tangible_ship_components_engine_shared_engine_incom_e16:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_incom_e16",

	attributes = {
		{"maxSpeed", 61.74},
		{"maxPitch", 59.625},
		{"maxRoll", 59.625},
		{"maxYaw", 59.625},
		{"currentHitpoints", 431.25},
		{"maximumHitpoints", 431.25},
		{"maximumArmorHitpoints", 215.625},
		{"currentArmorHitpoints", 215.625},
		{"efficiency", 1},
		{"energyMaintenance", 1575},
		{"mass", 3937.5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_engine_incom_e16, "object/tangible/ship/components/engine/engine_incom_e16.iff")
