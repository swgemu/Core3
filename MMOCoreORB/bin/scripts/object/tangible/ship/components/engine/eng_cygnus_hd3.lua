object_tangible_ship_components_engine_eng_cygnus_hd3 = object_tangible_ship_components_engine_shared_eng_cygnus_hd3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_cygnus_hd3",

	attributes = {
		{"maxSpeed", 44.1},
		{"maxPitch", 42.75},
		{"maxRoll", 42.75},
		{"maxYaw", 42.75},
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
		{"maxPitch", 0.09},
		{"maxRoll", 0.09},
		{"maxYaw", 0.09},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.14},
		{"mass", 0.14},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_cygnus_hd3, "object/tangible/ship/components/engine/eng_cygnus_hd3.iff")
