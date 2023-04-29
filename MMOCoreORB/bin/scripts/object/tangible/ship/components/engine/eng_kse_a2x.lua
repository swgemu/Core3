object_tangible_ship_components_engine_eng_kse_a2x = object_tangible_ship_components_engine_shared_eng_kse_a2x:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_kse_a2x",

	attributes = {
		{"maxSpeed", 42},
		{"maxPitch", 45},
		{"maxRoll", 45},
		{"maxYaw", 45},
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
		{"maxPitch", 0.07},
		{"maxRoll", 0.07},
		{"maxYaw", 0.07},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.14},
		{"mass", 0.14},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_kse_a2x, "object/tangible/ship/components/engine/eng_kse_a2x.iff")
