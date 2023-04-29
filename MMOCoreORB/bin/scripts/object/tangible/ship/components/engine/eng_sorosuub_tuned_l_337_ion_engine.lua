object_tangible_ship_components_engine_eng_sorosuub_tuned_l_337_ion_engine = object_tangible_ship_components_engine_shared_eng_sorosuub_tuned_l_337_ion_engine:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_sorosuub_tuned_l_337_ion_engine",

	attributes = {
		{"maxSpeed", 55.125},
		{"maxPitch", 56.25},
		{"maxRoll", 56.25},
		{"maxYaw", 56.25},
		{"currentHitpoints", 187.5},
		{"maximumHitpoints", 187.5},
		{"maximumArmorHitpoints", 93.75},
		{"currentArmorHitpoints", 93.75},
		{"efficiency", 1},
		{"energyMaintenance", 1500},
		{"mass", 1575},
		{"reverseEngineeringLevel", 2},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_sorosuub_tuned_l_337_ion_engine, "object/tangible/ship/components/engine/eng_sorosuub_tuned_l_337_ion_engine.iff")
