object_tangible_ship_components_engine_eng_moncal_heavy = object_tangible_ship_components_engine_shared_eng_moncal_heavy:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_moncal_heavy",

	attributes = {
		{"maxSpeed", 52.68},
		{"maxPitch", 50.56},
		{"maxRoll", 50.56},
		{"maxYaw", 50.56},
		{"currentHitpoints", 507.84},
		{"maximumHitpoints", 507.84},
		{"maximumArmorHitpoints", 253.92},
		{"currentArmorHitpoints", 253.92},
		{"efficiency", 1},
		{"energyMaintenance", 1350},
		{"mass", 6750},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_moncal_heavy, "object/tangible/ship/components/engine/eng_moncal_heavy.iff")
