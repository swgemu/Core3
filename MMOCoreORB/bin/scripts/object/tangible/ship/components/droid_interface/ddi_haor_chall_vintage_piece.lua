object_tangible_ship_components_droid_interface_ddi_haor_chall_vintage_piece = object_tangible_ship_components_droid_interface_shared_ddi_haor_chall_vintage_piece:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "ddi_haor_chall_vintage_piece",

	attributes = {
		{"commandSpeed", 29.25},
		{"currentHitpoints", 517.5},
		{"maximumHitpoints", 517.5},
		{"maximumArmorHitpointsMod", 0.05},
		{"maximumArmorHitpoints", 258.75},
		{"currentArmorHitpoints", 258.75},
		{"efficiency", 1},
		{"energyMaintenance", 500},
		{"mass", 2187.5},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"commandSpeed", 0.05},
		{"energyMaintenance", 0.05},
		{"mass", 0.05},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_droid_interface_ddi_haor_chall_vintage_piece, "object/tangible/ship/components/droid_interface/ddi_haor_chall_vintage_piece.iff")
