object_tangible_ship_components_weapon_wpn_seinar_ion_cannon = object_tangible_ship_components_weapon_shared_wpn_seinar_ion_cannon:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_seinar_ion_cannon",

	attributes = {
		{"minDamage", 373.375},
		{"maxDamage", 502.125},
		{"shieldEffectiveness", 0.875},
		{"armorEffectiveness", 0.375},
		{"energyPerShot", 25.5},
		{"refireRate", 0.425},
		{"currentHitpoints", 187.5},
		{"maximumHitpoints", 187.5},
		{"maximumArmorHitpoints", 93.75},
		{"currentArmorHitpoints", 93.75},
		{"efficiency", 1},
		{"energyMaintenance", 2200},
		{"mass", 1750},
		{"reverseEngineeringLevel", 2},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_seinar_ion_cannon, "object/tangible/ship/components/weapon/wpn_seinar_ion_cannon.iff")
