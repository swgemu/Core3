object_tangible_ship_components_engine_eng_kse_a5x = object_tangible_ship_components_engine_shared_eng_kse_a5x:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_kse_a5x",

	attributes = {
		{"maxSpeed", 51.744},
		{"maxPitch", 47.7},
		{"maxRoll", 47.7},
		{"maxYaw", 47.7},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 1575},
		{"mass", 2812.5},
		{"reverseEngineeringLevel", 3},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_kse_a5x, "object/tangible/ship/components/engine/eng_kse_a5x.iff")
