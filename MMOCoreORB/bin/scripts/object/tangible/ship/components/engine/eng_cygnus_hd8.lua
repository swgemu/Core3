object_tangible_ship_components_engine_eng_cygnus_hd8 = object_tangible_ship_components_engine_shared_eng_cygnus_hd8:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_cygnus_hd8",

	attributes = {
		{"maxSpeed", 65.85},
		{"maxPitch", 63.2},
		{"maxRoll", 63.2},
		{"maxYaw", 63.2},
		{"currentHitpoints", 793.5},
		{"maximumHitpoints", 793.5},
		{"maximumArmorHitpoints", 396.75},
		{"currentArmorHitpoints", 396.75},
		{"efficiency", 1},
		{"energyMaintenance", 1650},
		{"mass", 10815.8},
		{"reverseEngineeringLevel", 6},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_cygnus_hd8, "object/tangible/ship/components/engine/eng_cygnus_hd8.iff")
