object_tangible_ship_components_engine_engine_nubian_221_racing_mod = object_tangible_ship_components_engine_shared_engine_nubian_221_racing_mod:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_nubian_221_racing_mod",

	attributes = {
		{"maxSpeed", 82.6125},
		{"maxPitch", 71.0125},
		{"maxRoll", 71.0125},
		{"maxYaw", 71.0125},
		{"currentHitpoints", 1375.47},
		{"maximumHitpoints", 1375.47},
		{"maximumArmorHitpoints", 687.737},
		{"currentArmorHitpoints", 687.737},
		{"efficiency", 1},
		{"energyMaintenance", 1800},
		{"mass", 48645},
		{"reverseEngineeringLevel", 10},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_engine_nubian_221_racing_mod, "object/tangible/ship/components/engine/engine_nubian_221_racing_mod.iff")
