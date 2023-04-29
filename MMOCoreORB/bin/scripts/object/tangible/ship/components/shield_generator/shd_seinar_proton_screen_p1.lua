object_tangible_ship_components_shield_generator_shd_seinar_proton_screen_p1 = object_tangible_ship_components_shield_generator_shared_shd_seinar_proton_screen_p1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_seinar_proton_screen_p1",

	attributes = {
		{"shieldRechargeRate", 1.9},
		{"shieldHitpointsMaximumFront", 250},
		{"shieldHitpointsMaximumBack", 250},
		{"currentHitpoints", 168.75},
		{"maximumHitpoints", 168.75},
		{"maximumArmorHitpoints", 84.375},
		{"currentArmorHitpoints", 84.375},
		{"efficiency", 1},
		{"energyMaintenance", 2625},
		{"mass", 2117.5},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"shieldRechargeRate", 0.27},
		{"shieldHitpointsMaximumFront", 0.35},
		{"shieldHitpointsMaximumBack", 0.35},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_seinar_proton_screen_p1, "object/tangible/ship/components/shield_generator/shd_seinar_proton_screen_p1.iff")
