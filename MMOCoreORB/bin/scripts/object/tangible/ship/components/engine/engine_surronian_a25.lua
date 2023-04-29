object_tangible_ship_components_engine_engine_surronian_a25 = object_tangible_ship_components_engine_shared_engine_surronian_a25:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_surronian_a25",

	attributes = {
		{"maxSpeed", 44.688},
		{"maxPitch", 45.315},
		{"maxRoll", 45.315},
		{"maxYaw", 47.7},
		{"currentHitpoints", 327.75},
		{"maximumHitpoints", 327.75},
		{"maximumArmorHitpoints", 163.875},
		{"currentArmorHitpoints", 163.875},
		{"efficiency", 1},
		{"energyMaintenance", 1500},
		{"mass", 2250},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_engine_surronian_a25, "object/tangible/ship/components/engine/engine_surronian_a25.iff")
