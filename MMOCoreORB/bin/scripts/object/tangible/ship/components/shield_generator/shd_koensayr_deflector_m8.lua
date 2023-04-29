object_tangible_ship_components_shield_generator_shd_koensayr_deflector_m8 = object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_m8:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_koensayr_deflector_m8",

	attributes = {
		{"shieldRechargeRate", 10.217},
		{"shieldHitpointsMaximumFront", 1245.9},
		{"shieldHitpointsMaximumBack", 1245.9},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 3125},
		{"mass", 19734},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.341},
		{"shieldHitpointsMaximumBack", 0.341},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.35},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_koensayr_deflector_m8, "object/tangible/ship/components/shield_generator/shd_koensayr_deflector_m8.iff")
