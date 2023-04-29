object_tangible_ship_components_engine_engine_surronian_a2 = object_tangible_ship_components_engine_shared_engine_surronian_a2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_surronian_a2",

	attributes = {
		{"maxSpeed", 52.5},
		{"maxPitch", 56.25},
		{"maxRoll", 56.25},
		{"maxYaw", 56.25},
		{"currentHitpoints", 206.25},
		{"maximumHitpoints", 206.25},
		{"maximumArmorHitpoints", 103.125},
		{"currentArmorHitpoints", 103.125},
		{"efficiency", 1},
		{"energyMaintenance", 1500},
		{"mass", 1732.5},
		{"reverseEngineeringLevel", 2},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_engine_surronian_a2, "object/tangible/ship/components/engine/engine_surronian_a2.iff")
