object_tangible_ship_components_engine_eng_mandal_x37_vandal = object_tangible_ship_components_engine_shared_eng_mandal_x37_vandal:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_mandal_x37_vandal",

	attributes = {
		{"maxSpeed", 44.1},
		{"maxPitch", 47.25},
		{"maxRoll", 47.25},
		{"maxYaw", 47.25},
		{"currentHitpoints", 157.5},
		{"maximumHitpoints", 157.5},
		{"maximumArmorHitpoints", 78.75},
		{"currentArmorHitpoints", 78.75},
		{"efficiency", 1},
		{"energyMaintenance", 1575},
		{"mass", 945},
		{"reverseEngineeringLevel", 1},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_mandal_x37_vandal, "object/tangible/ship/components/engine/eng_mandal_x37_vandal.iff")
