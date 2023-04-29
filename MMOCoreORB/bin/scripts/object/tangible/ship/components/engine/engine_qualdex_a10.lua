object_tangible_ship_components_engine_engine_qualdex_a10 = object_tangible_ship_components_engine_shared_engine_qualdex_a10:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_qualdex_a10",

	attributes = {
		{"maxSpeed", 50.046},
		{"maxPitch", 48.032},
		{"maxRoll", 48.032},
		{"maxYaw", 50.56},
		{"currentHitpoints", 603.06},
		{"maximumHitpoints", 603.06},
		{"maximumArmorHitpoints", 301.53},
		{"currentArmorHitpoints", 301.53},
		{"efficiency", 1},
		{"energyMaintenance", 1575},
		{"mass", 5906.25},
		{"reverseEngineeringLevel", 5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_engine_qualdex_a10, "object/tangible/ship/components/engine/engine_qualdex_a10.iff")
