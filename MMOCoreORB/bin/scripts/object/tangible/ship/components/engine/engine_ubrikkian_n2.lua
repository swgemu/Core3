object_tangible_ship_components_engine_engine_ubrikkian_n2 = object_tangible_ship_components_engine_shared_engine_ubrikkian_n2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_ubrikkian_n2",

	attributes = {
		{"maxSpeed", 66.09},
		{"maxPitch", 59.6505},
		{"maxRoll", 59.6505},
		{"maxYaw", 59.6505},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 1800},
		{"mass", 42120},
		{"reverseEngineeringLevel", 9},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_engine_ubrikkian_n2, "object/tangible/ship/components/engine/engine_ubrikkian_n2.iff")
