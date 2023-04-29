object_tangible_ship_components_weapon_wpn_subpro_modified_tricannon = object_tangible_ship_components_weapon_shared_wpn_subpro_modified_tricannon:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_subpro_modified_tricannon",

	attributes = {
		{"minDamage", 761.25},
		{"maxDamage", 1072.5},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 28.05},
		{"refireRate", 0.425},
		{"currentHitpoints", 431.25},
		{"maximumHitpoints", 431.25},
		{"maximumArmorHitpoints", 215.625},
		{"currentArmorHitpoints", 215.625},
		{"efficiency", 1},
		{"energyMaintenance", 2100},
		{"mass", 4593.75},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"minDamage", 0.12},
		{"maxDamage", 0.12},
		{"shieldEffectiveness", 0.05},
		{"armorEffectiveness", 0.05},
		{"energyPerShot", 0.17},
		{"refireRate", 0.05},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.17},
		{"mass", 0.17},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_subpro_modified_tricannon, "object/tangible/ship/components/weapon/wpn_subpro_modified_tricannon.iff")
