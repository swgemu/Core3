object_tangible_ship_components_engine_eng_subpro_light_engines = object_tangible_ship_components_engine_shared_eng_subpro_light_engines:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_subpro_light_engines",

	attributes = {
		{"maxSpeed", 42},
		{"maxPitch", 47.25},
		{"maxRoll", 47.25},
		{"maxYaw", 47.25},
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
		{"maxPitch", 0.06},
		{"maxRoll", 0.06},
		{"maxYaw", 0.06},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.14},
		{"mass", 0.14},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_subpro_light_engines, "object/tangible/ship/components/engine/eng_subpro_light_engines.iff")
