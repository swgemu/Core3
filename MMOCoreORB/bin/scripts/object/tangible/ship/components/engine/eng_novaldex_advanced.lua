object_tangible_ship_components_engine_eng_novaldex_advanced = object_tangible_ship_components_engine_shared_eng_novaldex_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_novaldex_advanced",

	attributes = {
		{"maxSpeed", 62.7855},
		{"maxPitch", 53.9695},
		{"maxRoll", 53.9695},
		{"maxYaw", 56.81},
		{"currentHitpoints", 1045.36},
		{"maximumHitpoints", 1045.36},
		{"maximumArmorHitpoints", 522.68},
		{"currentArmorHitpoints", 522.68},
		{"efficiency", 1},
		{"energyMaintenance", 1725},
		{"mass", 40365},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_novaldex_advanced, "object/tangible/ship/components/engine/eng_novaldex_advanced.iff")
