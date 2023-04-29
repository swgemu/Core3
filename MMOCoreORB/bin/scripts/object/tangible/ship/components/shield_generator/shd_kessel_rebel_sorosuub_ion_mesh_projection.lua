object_tangible_ship_components_shield_generator_shd_kessel_rebel_sorosuub_ion_mesh_projection = object_tangible_ship_components_shield_generator_shared_shd_kessel_rebel_sorosuub_ion_mesh_projection:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "shd_kessel_rebel_sorosuub_ion_mesh_projection",

	attributes = {
		{"shieldRechargeRate", 12.836},
		{"shieldHitpointsMaximumFront", 1604.72},
		{"shieldHitpointsMaximumBack", 1604.72},
		{"currentHitpoints", 1788.12},
		{"maximumHitpoints", 1788.12},
		{"maximumArmorHitpoints", 894.059},
		{"currentArmorHitpoints", 894.059},
		{"efficiency", 1},
		{"energyMaintenance", 3056},
		{"mass", 62040},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"shieldRechargeRate", 0.26},
		{"shieldHitpointsMaximumFront", 0.341},
		{"shieldHitpointsMaximumBack", 0.341},
		{"maximumArmorHitpoints", 0.07},
		{"energyMaintenance", 0.3},
		{"mass", 0.2},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_shield_generator_shd_kessel_rebel_sorosuub_ion_mesh_projection, "object/tangible/ship/components/shield_generator/shd_kessel_rebel_sorosuub_ion_mesh_projection.iff")
