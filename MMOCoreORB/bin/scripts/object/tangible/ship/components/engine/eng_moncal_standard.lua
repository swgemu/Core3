object_tangible_ship_components_engine_eng_moncal_standard = object_tangible_ship_components_engine_shared_eng_moncal_standard:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_moncal_standard",

	attributes = {
		{"maxSpeed", 49.392},
		{"maxPitch", 45.315},
		{"maxRoll", 45.315},
		{"maxYaw", 45.315},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 1575},
		{"mass", 2362.5},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maxSpeed", 0.1},
		{"maxPitch", 0.09},
		{"maxRoll", 0.09},
		{"maxYaw", 0.09},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.14},
		{"mass", 0.14},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_moncal_standard, "object/tangible/ship/components/engine/eng_moncal_standard.iff")
