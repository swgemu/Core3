object_tangible_ship_components_weapon_wpn_armek_elite = object_tangible_ship_components_weapon_shared_wpn_armek_elite:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "wpn_armek_elite",

	attributes = {
		{"minDamage", 2476.62},
		{"maxDamage", 4011.81},
		{"shieldEffectiveness", 0.75},
		{"armorEffectiveness", 0.563},
		{"energyPerShot", 37.335},
		{"refireRate", 0.425},
		{"currentHitpoints", 1237.93},
		{"maximumHitpoints", 1237.93},
		{"maximumArmorHitpoints", 618.964},
		{"currentArmorHitpoints", 618.964},
		{"efficiency", 1},
		{"energyMaintenance", 2400},
		{"mass", 51700},
		{"reverseEngineeringLevel", 10},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_wpn_armek_elite, "object/tangible/ship/components/weapon/wpn_armek_elite.iff")
