object_tangible_ship_components_engine_eng_qualdex_small_kyromaster = object_tangible_ship_components_engine_shared_eng_qualdex_small_kyromaster:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_qualdex_small_kyromaster",

	attributes = {
		{"maxSpeed", 42},
		{"maxPitch", 45},
		{"maxRoll", 45},
		{"maxYaw", 45},
		{"currentHitpoints", 142.5},
		{"maximumHitpoints", 142.5},
		{"maximumArmorHitpoints", 71.25},
		{"currentArmorHitpoints", 71.25},
		{"efficiency", 1},
		{"energyMaintenance", 1425},
		{"mass", 900},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_qualdex_small_kyromaster, "object/tangible/ship/components/engine/eng_qualdex_small_kyromaster.iff")
