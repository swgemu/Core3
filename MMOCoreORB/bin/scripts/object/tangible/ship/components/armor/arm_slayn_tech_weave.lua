object_tangible_ship_components_armor_arm_slayn_tech_weave = object_tangible_ship_components_armor_shared_arm_slayn_tech_weave:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "arm_slayn_tech_weave",

	attributes = {
		{"currentHitpoints", 206},
		{"maximumHitpoints", 206},
		{"maximumArmorHitpoints", 206},
		{"currentArmorHitpoints", 206},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 1545.07},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maximumArmorHitpoints", 0.38},
		{"energyMaintenance", 0},
		{"mass", 0.24},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_armor_arm_slayn_tech_weave, "object/tangible/ship/components/armor/arm_slayn_tech_weave.iff")
