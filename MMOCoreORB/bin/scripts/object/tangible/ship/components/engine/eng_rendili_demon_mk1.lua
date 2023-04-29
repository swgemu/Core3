object_tangible_ship_components_engine_eng_rendili_demon_mk1 = object_tangible_ship_components_engine_shared_eng_rendili_demon_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_rendili_demon_mk1",

	attributes = {
		{"maxSpeed", 52.68},
		{"maxPitch", 50.56},
		{"maxRoll", 50.56},
		{"maxYaw", 50.56},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 1650},
		{"mass", 6187.5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_rendili_demon_mk1, "object/tangible/ship/components/engine/eng_rendili_demon_mk1.iff")
