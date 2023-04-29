object_tangible_ship_components_armor_arm_kessel_rebel_slayn_flexsteel_multilayer = object_tangible_ship_components_armor_shared_arm_kessel_rebel_slayn_flexsteel_multilayer:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_kessel_rebel_slayn_flexsteel_multilayer",

	attributes = {
		{"currentHitpoints", 1833.96},
		{"maximumHitpoints", 1833.96},
		{"maximumArmorHitpoints", 1833.96},
		{"currentArmorHitpoints", 1833.96},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 46530},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.25},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_kessel_rebel_slayn_flexsteel_multilayer, "object/tangible/ship/components/armor/arm_kessel_rebel_slayn_flexsteel_multilayer.iff")
