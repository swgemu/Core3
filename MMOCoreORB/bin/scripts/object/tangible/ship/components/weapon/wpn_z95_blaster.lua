object_tangible_ship_components_weapon_wpn_z95_blaster = object_tangible_ship_components_weapon_shared_wpn_z95_blaster:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_z95_blaster",

	attributes = {
		{"minDamage", 362.5},
		{"maxDamage", 487.5},
		{"shieldEffectiveness", 0.625},
		{"armorEffectiveness", 0.625},
		{"energyPerShot", 25.5},
		{"refireRate", 0.425},
		{"currentHitpoints", 187.5},
		{"maximumHitpoints", 187.5},
		{"maximumArmorHitpoints", 93.75},
		{"currentArmorHitpoints", 93.75},
		{"efficiency", 1},
		{"energyMaintenance", 2000},
		{"mass", 1750},
		{"reverseEngineeringLevel", 2},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_z95_blaster, "object/tangible/ship/components/weapon/wpn_z95_blaster.iff")
