object_tangible_ship_components_shield_generator_shd_taim_standard = object_tangible_ship_components_shield_generator_shared_shd_taim_standard:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_taim_standard",

	attributes = {
		{"shieldRechargeRate", 4.887},
		{"shieldHitpointsMaximumFront", 575},
		{"shieldHitpointsMaximumBack", 575},
		{"currentHitpoints", 431.25},
		{"maximumHitpoints", 431.25},
		{"maximumArmorHitpoints", 215.625},
		{"currentArmorHitpoints", 215.625},
		{"efficiency", 1},
		{"energyMaintenance", 2875},
		{"mass", 5053.12},
		{"reverseEngineeringLevel", 4},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_taim_standard, "object/tangible/ship/components/shield_generator/shd_taim_standard.iff")
