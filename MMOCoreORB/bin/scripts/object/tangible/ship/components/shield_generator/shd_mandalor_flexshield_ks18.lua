object_tangible_ship_components_shield_generator_shd_mandalor_flexshield_ks18 = object_tangible_ship_components_shield_generator_shared_shd_mandalor_flexshield_ks18:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_mandalor_flexshield_ks18",

	attributes = {
		{"shieldRechargeRate", 6.937},
		{"shieldHitpointsMaximumFront", 846.4},
		{"shieldHitpointsMaximumBack", 846.4},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 2806},
		{"mass", 7562.5},
		{"reverseEngineeringLevel", 5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_mandalor_flexshield_ks18, "object/tangible/ship/components/shield_generator/shd_mandalor_flexshield_ks18.iff")
