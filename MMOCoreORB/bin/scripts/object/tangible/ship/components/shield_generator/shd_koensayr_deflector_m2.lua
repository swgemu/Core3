object_tangible_ship_components_shield_generator_shd_koensayr_deflector_m2 = object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_m2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_koensayr_deflector_m2",

	attributes = {
		{"shieldRechargeRate", 3.772},
		{"shieldHitpointsMaximumFront", 460},
		{"shieldHitpointsMaximumBack", 460},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 2681},
		{"mass", 2887.5},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"shieldRechargeRate", 0.15},
		{"shieldHitpointsMaximumFront", 0.345},
		{"shieldHitpointsMaximumBack", 0.345},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_koensayr_deflector_m2, "object/tangible/ship/components/shield_generator/shd_koensayr_deflector_m2.iff")
