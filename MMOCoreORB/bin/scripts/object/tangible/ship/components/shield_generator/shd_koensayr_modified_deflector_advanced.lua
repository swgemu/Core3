object_tangible_ship_components_shield_generator_shd_koensayr_modified_deflector_advanced = object_tangible_ship_components_shield_generator_shared_shd_koensayr_modified_deflector_advanced:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_koensayr_modified_deflector_advanced",

	attributes = {
		{"shieldRechargeRate", 11.149},
		{"shieldHitpointsMaximumFront", 1467.18},
		{"shieldHitpointsMaximumBack", 1467.18},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 3056},
		{"mass", 55770},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.35},
		{"shieldHitpointsMaximumBack", 0.35},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_koensayr_modified_deflector_advanced, "object/tangible/ship/components/shield_generator/shd_koensayr_modified_deflector_advanced.iff")
