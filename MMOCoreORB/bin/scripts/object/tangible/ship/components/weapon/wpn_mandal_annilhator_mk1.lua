object_tangible_ship_components_weapon_wpn_mandal_annilhator_mk1 = object_tangible_ship_components_weapon_shared_wpn_mandal_annilhator_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_mandal_annilhator_mk1",

	attributes = {
		{"minDamage", 1383.14},
		{"maxDamage", 2041.43},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 30.855},
		{"refireRate", 0.425},
		{"currentHitpoints", 793.5},
		{"maximumHitpoints", 793.5},
		{"maximumArmorHitpoints", 396.75},
		{"currentArmorHitpoints", 396.75},
		{"efficiency", 1},
		{"energyMaintenance", 2400},
		{"mass", 12017.5},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"minDamage", 0.14},
		{"maxDamage", 0.14},
		{"shieldEffectiveness", 0.05},
		{"armorEffectiveness", 0.05},
		{"energyPerShot", 0.17},
		{"refireRate", 0.05},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.17},
		{"mass", 0.17},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_mandal_annilhator_mk1, "object/tangible/ship/components/weapon/wpn_mandal_annilhator_mk1.iff")
