object_tangible_ship_components_engine_eng_sorosuub_l_337_ion_engine = object_tangible_ship_components_engine_shared_eng_sorosuub_l_337_ion_engine:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_sorosuub_l_337_ion_engine",

	attributes = {
		{"maxSpeed", 39.9},
		{"maxPitch", 42.75},
		{"maxRoll", 42.75},
		{"maxYaw", 45},
		{"currentHitpoints", 142.5},
		{"maximumHitpoints", 142.5},
		{"maximumArmorHitpoints", 71.25},
		{"currentArmorHitpoints", 71.25},
		{"efficiency", 1},
		{"energyMaintenance", 1425},
		{"mass", 855},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_sorosuub_l_337_ion_engine, "object/tangible/ship/components/engine/eng_sorosuub_l_337_ion_engine.iff")
