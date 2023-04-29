object_tangible_ship_components_engine_eng_haor_chall_old_engine = object_tangible_ship_components_engine_shared_eng_haor_chall_old_engine:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_haor_chall_old_engine",

	attributes = {
		{"maxSpeed", 42},
		{"maxPitch", 45},
		{"maxRoll", 45},
		{"maxYaw", 45},
		{"currentHitpoints", 120},
		{"maximumHitpoints", 120},
		{"maximumArmorHitpoints", 60},
		{"currentArmorHitpoints", 60},
		{"efficiency", 1},
		{"energyMaintenance", 1200},
		{"mass", 990},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_haor_chall_old_engine, "object/tangible/ship/components/engine/eng_haor_chall_old_engine.iff")
