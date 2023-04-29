object_tangible_ship_components_shield_generator_shd_dual_deflector_s2 = object_tangible_ship_components_shield_generator_shared_shd_dual_deflector_s2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_dual_deflector_s2",

	attributes = {
		{"shieldRechargeRate", 1.64},
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
		{"shieldRechargeRate", 0.15},
		{"shieldHitpointsMaximumFront", 0.345},
		{"shieldHitpointsMaximumBack", 0.345},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_dual_deflector_s2, "object/tangible/ship/components/shield_generator/shd_dual_deflector_s2.iff")
