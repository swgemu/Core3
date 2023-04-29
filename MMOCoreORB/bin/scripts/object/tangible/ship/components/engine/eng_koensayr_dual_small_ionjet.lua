object_tangible_ship_components_engine_eng_koensayr_dual_small_ionjet = object_tangible_ship_components_engine_shared_eng_koensayr_dual_small_ionjet:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_koensayr_dual_small_ionjet",

	attributes = {
		{"maxSpeed", 47.04},
		{"maxPitch", 47.7},
		{"maxRoll", 47.7},
		{"maxYaw", 47.7},
		{"currentHitpoints", 276},
		{"maximumHitpoints", 276},
		{"maximumArmorHitpoints", 138},
		{"currentArmorHitpoints", 138},
		{"efficiency", 1},
		{"energyMaintenance", 1275},
		{"mass", 2587.5},
		{"reverseEngineeringLevel", 3},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_koensayr_dual_small_ionjet, "object/tangible/ship/components/engine/eng_koensayr_dual_small_ionjet.iff")
