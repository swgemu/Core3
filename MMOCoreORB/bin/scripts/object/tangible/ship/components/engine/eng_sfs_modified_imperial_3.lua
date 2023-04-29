object_tangible_ship_components_engine_eng_sfs_modified_imperial_3 = object_tangible_ship_components_engine_shared_eng_sfs_modified_imperial_3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_sfs_modified_imperial_3",

	attributes = {
		{"maxSpeed", 65.85},
		{"maxPitch", 63.2},
		{"maxRoll", 63.2},
		{"maxYaw", 63.2},
		{"currentHitpoints", 753.825},
		{"maximumHitpoints", 753.825},
		{"maximumArmorHitpoints", 376.913},
		{"currentArmorHitpoints", 376.913},
		{"efficiency", 1},
		{"energyMaintenance", 1575},
		{"mass", 10815.8},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_sfs_modified_imperial_3, "object/tangible/ship/components/engine/eng_sfs_modified_imperial_3.iff")
