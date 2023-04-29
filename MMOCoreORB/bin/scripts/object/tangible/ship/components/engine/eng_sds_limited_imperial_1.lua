object_tangible_ship_components_engine_eng_sds_limited_imperial_1 = object_tangible_ship_components_engine_shared_eng_sds_limited_imperial_1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_sds_limited_imperial_1",

	attributes = {
		{"maxSpeed", 52.5},
		{"maxPitch", 56.25},
		{"maxRoll", 56.25},
		{"maxYaw", 56.25},
		{"currentHitpoints", 178.125},
		{"maximumHitpoints", 178.125},
		{"maximumArmorHitpoints", 89.0625},
		{"currentArmorHitpoints", 89.0625},
		{"efficiency", 1},
		{"energyMaintenance", 1425},
		{"mass", 1575},
		{"reverseEngineeringLevel", 2},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_sds_limited_imperial_1, "object/tangible/ship/components/engine/eng_sds_limited_imperial_1.iff")
