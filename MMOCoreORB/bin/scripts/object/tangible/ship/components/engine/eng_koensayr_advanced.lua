object_tangible_ship_components_engine_eng_koensayr_advanced = object_tangible_ship_components_engine_shared_eng_koensayr_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_koensayr_advanced",

	attributes = {
		{"maxSpeed", 66.09},
		{"maxPitch", 56.81},
		{"maxRoll", 56.81},
		{"maxYaw", 56.81},
		{"currentHitpoints", 880.304},
		{"maximumHitpoints", 880.304},
		{"maximumArmorHitpoints", 440.152},
		{"currentArmorHitpoints", 440.152},
		{"efficiency", 1},
		{"energyMaintenance", 1500},
		{"mass", 45630},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_koensayr_advanced, "object/tangible/ship/components/engine/eng_koensayr_advanced.iff")
