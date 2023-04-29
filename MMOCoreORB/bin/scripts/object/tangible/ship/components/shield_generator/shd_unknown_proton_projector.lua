object_tangible_ship_components_shield_generator_shd_unknown_proton_projector = object_tangible_ship_components_shield_generator_shared_shd_unknown_proton_projector:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_unknown_proton_projector",

	attributes = {
		{"shieldRechargeRate", 1.9},
		{"shieldHitpointsMaximumFront", 250},
		{"shieldHitpointsMaximumBack", 250},
		{"currentHitpoints", 187.5},
		{"maximumHitpoints", 187.5},
		{"maximumArmorHitpoints", 93.75},
		{"currentArmorHitpoints", 93.75},
		{"efficiency", 1},
		{"energyMaintenance", 2556},
		{"mass", 1925},
		{"reverseEngineeringLevel", 2},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_unknown_proton_projector, "object/tangible/ship/components/shield_generator/shd_unknown_proton_projector.iff")
