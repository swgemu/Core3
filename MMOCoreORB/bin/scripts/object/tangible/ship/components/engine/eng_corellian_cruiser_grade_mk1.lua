object_tangible_ship_components_engine_eng_corellian_cruiser_grade_mk1 = object_tangible_ship_components_engine_shared_eng_corellian_cruiser_grade_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_corellian_cruiser_grade_mk1",

	attributes = {
		{"maxSpeed", 42},
		{"maxPitch", 45},
		{"maxRoll", 45},
		{"maxYaw", 45},
		{"currentHitpoints", 165},
		{"maximumHitpoints", 165},
		{"maximumArmorHitpoints", 82.5},
		{"currentArmorHitpoints", 82.5},
		{"efficiency", 1},
		{"energyMaintenance", 1500},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_corellian_cruiser_grade_mk1, "object/tangible/ship/components/engine/eng_corellian_cruiser_grade_mk1.iff")
