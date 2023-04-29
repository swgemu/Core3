object_tangible_ship_components_weapon_capacitor_cap_tiefighter_elite_mk1 = object_tangible_ship_components_weapon_capacitor_shared_cap_tiefighter_elite_mk1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_tiefighter_elite_mk1",

	attributes = {
		{"currentEnergy", 577.5},
		{"maxEnergy", 577.5},
		{"rechargeRate", 23.1},
		{"currentHitpoints", 379.5},
		{"maximumHitpoints", 379.5},
		{"maximumArmorHitpoints", 189.75},
		{"currentArmorHitpoints", 189.75},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 2750},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_tiefighter_elite_mk1, "object/tangible/ship/components/weapon_capacitor/cap_tiefighter_elite_mk1.iff")
