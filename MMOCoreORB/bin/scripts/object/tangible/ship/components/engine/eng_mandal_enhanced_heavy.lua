object_tangible_ship_components_engine_eng_mandal_enhanced_heavy = object_tangible_ship_components_engine_shared_eng_mandal_enhanced_heavy:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_mandal_enhanced_heavy",

	attributes = {
		{"maxSpeed", 65.85},
		{"maxPitch", 63.2},
		{"maxRoll", 63.2},
		{"maxYaw", 63.2},
		{"currentHitpoints", 872.85},
		{"maximumHitpoints", 872.85},
		{"maximumArmorHitpoints", 436.425},
		{"currentArmorHitpoints", 436.425},
		{"efficiency", 1},
		{"energyMaintenance", 1650},
		{"mass", 11799},
		{"reverseEngineeringLevel", 6},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_mandal_enhanced_heavy, "object/tangible/ship/components/engine/eng_mandal_enhanced_heavy.iff")
