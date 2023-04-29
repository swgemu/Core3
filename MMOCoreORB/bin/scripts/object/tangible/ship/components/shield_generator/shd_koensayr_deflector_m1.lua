object_tangible_ship_components_shield_generator_shd_koensayr_deflector_m1 = object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_m1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_koensayr_deflector_m1",

	attributes = {
		{"shieldRechargeRate", 1.52},
		{"shieldHitpointsMaximumFront", 200},
		{"shieldHitpointsMaximumBack", 200},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 2556},
		{"mass", 1100},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"shieldRechargeRate", 0.22},
		{"shieldHitpointsMaximumFront", 0.32},
		{"shieldHitpointsMaximumBack", 0.32},
		{"maximumArmorHitpoints", 0.04},
		{"energyMaintenance", 0.2},
		{"mass", 0.1},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_koensayr_deflector_m1, "object/tangible/ship/components/shield_generator/shd_koensayr_deflector_m1.iff")
