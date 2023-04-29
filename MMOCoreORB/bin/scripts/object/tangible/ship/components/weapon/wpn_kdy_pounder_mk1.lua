object_tangible_ship_components_weapon_wpn_kdy_pounder_mk1 = object_tangible_ship_components_weapon_shared_wpn_kdy_pounder_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_kdy_pounder_mk1",

	attributes = {
		{"minDamage", 685.125},
		{"maxDamage", 965.25},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 28.05},
		{"refireRate", 0.408},
		{"currentHitpoints", 431.25},
		{"maximumHitpoints", 431.25},
		{"maximumArmorHitpoints", 215.625},
		{"currentArmorHitpoints", 215.625},
		{"efficiency", 1},
		{"energyMaintenance", 1900},
		{"mass", 4593.75},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"minDamage", 0.12},
		{"maxDamage", 0.12},
		{"shieldEffectiveness", 0.05},
		{"armorEffectiveness", 0.05},
		{"energyPerShot", 0.16},
		{"refireRate", 0.05},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.17},
		{"mass", 0.17},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_kdy_pounder_mk1, "object/tangible/ship/components/weapon/wpn_kdy_pounder_mk1.iff")
