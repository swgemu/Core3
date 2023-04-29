object_tangible_ship_components_engine_engine_kongar_defender = object_tangible_ship_components_engine_shared_engine_kongar_defender:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_kongar_defender",

	attributes = {
		{"maxSpeed", 58.8},
		{"maxPitch", 59.625},
		{"maxRoll", 59.625},
		{"maxYaw", 59.625},
		{"currentHitpoints", 409.688},
		{"maximumHitpoints", 409.688},
		{"maximumArmorHitpoints", 204.844},
		{"currentArmorHitpoints", 204.844},
		{"efficiency", 1},
		{"energyMaintenance", 1500},
		{"mass", 4134.38},
		{"reverseEngineeringLevel", 4},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_engine_kongar_defender, "object/tangible/ship/components/engine/engine_kongar_defender.iff")
