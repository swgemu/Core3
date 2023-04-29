object_tangible_ship_components_engine_eng_incom_fusialthrust = object_tangible_ship_components_engine_shared_eng_incom_fusialthrust:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_incom_fusialthrust",

	attributes = {
		{"maxSpeed", 58.8},
		{"maxPitch", 59.625},
		{"maxRoll", 59.625},
		{"maxYaw", 59.625},
		{"currentHitpoints", 431.25},
		{"maximumHitpoints", 431.25},
		{"maximumArmorHitpoints", 215.625},
		{"currentArmorHitpoints", 215.625},
		{"efficiency", 1},
		{"energyMaintenance", 1575},
		{"mass", 4134.38},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_incom_fusialthrust, "object/tangible/ship/components/engine/eng_incom_fusialthrust.iff")
