object_tangible_ship_components_reactor_rct_armek_ultra_collider = object_tangible_ship_components_reactor_shared_rct_armek_ultra_collider:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "rct_armek_ultra_collider",

	attributes = {
		{"energyGeneration", 27600},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 0},
		{"mass", 51480},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"energyGeneration", 0.177},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0},
		{"mass", 0.28},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_reactor_rct_armek_ultra_collider, "object/tangible/ship/components/reactor/rct_armek_ultra_collider.iff")
