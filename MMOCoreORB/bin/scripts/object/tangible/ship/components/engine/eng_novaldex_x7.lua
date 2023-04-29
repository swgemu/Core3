object_tangible_ship_components_engine_eng_novaldex_x7 = object_tangible_ship_components_engine_shared_eng_novaldex_x7:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_novaldex_x7",

	attributes = {
		{"maxSpeed", 59.01},
		{"maxPitch", 53.6},
		{"maxRoll", 53.6},
		{"maxYaw", 53.6},
		{"currentHitpoints", 747.544},
		{"maximumHitpoints", 747.544},
		{"maximumArmorHitpoints", 373.772},
		{"currentArmorHitpoints", 373.772},
		{"efficiency", 1},
		{"energyMaintenance", 1425},
		{"mass", 17550},
		{"reverseEngineeringLevel", 7},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_novaldex_x7, "object/tangible/ship/components/engine/eng_novaldex_x7.iff")
