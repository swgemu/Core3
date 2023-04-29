object_tangible_ship_components_engine_engine_kuat_a9x = object_tangible_ship_components_engine_shared_engine_kuat_a9x:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_kuat_a9x",

	attributes = {
		{"maxSpeed", 56.0595},
		{"maxPitch", 50.92},
		{"maxRoll", 50.92},
		{"maxYaw", 53.6},
		{"currentHitpoints", 887.708},
		{"maximumHitpoints", 887.708},
		{"maximumArmorHitpoints", 443.854},
		{"currentArmorHitpoints", 443.854},
		{"efficiency", 1},
		{"energyMaintenance", 1650},
		{"mass", 15444},
		{"reverseEngineeringLevel", 7},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_engine_kuat_a9x, "object/tangible/ship/components/engine/engine_kuat_a9x.iff")
