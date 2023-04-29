object_tangible_ship_components_engine_eng_incom_light_fusialthrust = object_tangible_ship_components_engine_shared_eng_incom_light_fusialthrust:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_incom_light_fusialthrust",

	attributes = {
		{"maxSpeed", 35.7},
		{"maxPitch", 45},
		{"maxRoll", 45},
		{"maxYaw", 45},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 1500},
		{"mass", 765},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_incom_light_fusialthrust, "object/tangible/ship/components/engine/eng_incom_light_fusialthrust.iff")
