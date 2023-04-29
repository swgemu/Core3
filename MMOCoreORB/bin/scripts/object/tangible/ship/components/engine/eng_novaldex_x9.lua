object_tangible_ship_components_engine_eng_novaldex_x9 = object_tangible_ship_components_engine_shared_eng_novaldex_x9:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_novaldex_x9",

	attributes = {
		{"maxSpeed", 77.4506},
		{"maxPitch", 67},
		{"maxRoll", 67},
		{"maxYaw", 67},
		{"currentHitpoints", 1168.04},
		{"maximumHitpoints", 1168.04},
		{"maximumArmorHitpoints", 584.019},
		{"currentArmorHitpoints", 584.019},
		{"efficiency", 1},
		{"energyMaintenance", 1725},
		{"mass", 27027},
		{"reverseEngineeringLevel", 8},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_novaldex_x9, "object/tangible/ship/components/engine/eng_novaldex_x9.iff")
