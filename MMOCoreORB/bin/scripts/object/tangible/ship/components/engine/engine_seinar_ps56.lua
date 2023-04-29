object_tangible_ship_components_engine_engine_seinar_ps56 = object_tangible_ship_components_engine_shared_engine_seinar_ps56:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_seinar_ps56",

	attributes = {
		{"maxSpeed", 49.392},
		{"maxPitch", 50.085},
		{"maxRoll", 50.085},
		{"maxYaw", 50.085},
		{"currentHitpoints", 362.25},
		{"maximumHitpoints", 362.25},
		{"maximumArmorHitpoints", 181.125},
		{"currentArmorHitpoints", 181.125},
		{"efficiency", 1},
		{"energyMaintenance", 1650},
		{"mass", 2475},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_engine_seinar_ps56, "object/tangible/ship/components/engine/engine_seinar_ps56.iff")
