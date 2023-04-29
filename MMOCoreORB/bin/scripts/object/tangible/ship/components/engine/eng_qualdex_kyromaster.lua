object_tangible_ship_components_engine_eng_qualdex_kyromaster = object_tangible_ship_components_engine_shared_eng_qualdex_kyromaster:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_qualdex_kyromaster",

	attributes = {
		{"maxSpeed", 47.04},
		{"maxPitch", 50.085},
		{"maxRoll", 50.085},
		{"maxYaw", 50.085},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 1575},
		{"mass", 2362.5},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maxSpeed", 0.1},
		{"maxPitch", 0.06},
		{"maxRoll", 0.06},
		{"maxYaw", 0.06},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.14},
		{"mass", 0.14},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_qualdex_kyromaster, "object/tangible/ship/components/engine/eng_qualdex_kyromaster.iff")
