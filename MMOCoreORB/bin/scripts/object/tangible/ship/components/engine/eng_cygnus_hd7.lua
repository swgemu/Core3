object_tangible_ship_components_engine_eng_cygnus_hd7 = object_tangible_ship_components_engine_shared_eng_cygnus_hd7:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_cygnus_hd7",

	attributes = {
		{"maxSpeed", 47.04},
		{"maxPitch", 47.7},
		{"maxRoll", 47.7},
		{"maxYaw", 47.7},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 1575},
		{"mass", 2362.5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_cygnus_hd7, "object/tangible/ship/components/engine/eng_cygnus_hd7.iff")
