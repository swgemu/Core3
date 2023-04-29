object_tangible_ship_components_engine_eng_qualdex_advanced = object_tangible_ship_components_engine_shared_eng_qualdex_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_qualdex_advanced",

	attributes = {
		{"maxSpeed", 69.3945},
		{"maxPitch", 59.6505},
		{"maxRoll", 59.6505},
		{"maxYaw", 59.6505},
		{"currentHitpoints", 1155.4},
		{"maximumHitpoints", 1155.4},
		{"maximumArmorHitpoints", 577.7},
		{"currentArmorHitpoints", 577.7},
		{"efficiency", 1},
		{"energyMaintenance", 1875},
		{"mass", 43875},
		{"reverseEngineeringLevel", 9},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_qualdex_advanced, "object/tangible/ship/components/engine/eng_qualdex_advanced.iff")
