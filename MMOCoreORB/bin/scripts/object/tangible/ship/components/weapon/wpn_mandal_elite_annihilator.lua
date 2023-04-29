object_tangible_ship_components_weapon_wpn_mandal_elite_annihilator = object_tangible_ship_components_weapon_shared_wpn_mandal_elite_annihilator:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_mandal_elite_annihilator",

	attributes = {
		{"minDamage", 2476.62},
		{"maxDamage", 4011.81},
		{"shieldEffectiveness", 0.563},
		{"armorEffectiveness", 0.563},
		{"energyPerShot", 37.335},
		{"refireRate", 0.40375},
		{"currentHitpoints", 1513.02},
		{"maximumHitpoints", 1513.02},
		{"maximumArmorHitpoints", 756.511},
		{"currentArmorHitpoints", 756.511},
		{"efficiency", 1},
		{"energyMaintenance", 2400},
		{"mass", 61100},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"minDamage", 0.12},
		{"maxDamage", 0.12},
		{"shieldEffectiveness", 0.06},
		{"armorEffectiveness", 0.06},
		{"energyPerShot", 0.17},
		{"refireRate", 0.05},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.17},
		{"mass", 0.17},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_mandal_elite_annihilator, "object/tangible/ship/components/weapon/wpn_mandal_elite_annihilator.iff")
