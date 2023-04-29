object_tangible_ship_components_engine_eng_kessel_imperial_rendili_hyperion_drive = object_tangible_ship_components_engine_shared_eng_kessel_imperial_rendili_hyperion_drive:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "eng_kessel_imperial_rendili_hyperion_drive",

	attributes = {
		{"maxSpeed", 69.3945},
		{"maxPitch", 56.81},
		{"maxRoll", 56.81},
		{"maxYaw", 56.81},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 1800},
		{"mass", 40365},
		{"reverseEngineeringLevel", 9},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_engine_eng_kessel_imperial_rendili_hyperion_drive, "object/tangible/ship/components/engine/eng_kessel_imperial_rendili_hyperion_drive.iff")
