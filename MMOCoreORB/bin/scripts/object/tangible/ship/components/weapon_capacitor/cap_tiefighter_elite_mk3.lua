object_tangible_ship_components_weapon_capacitor_cap_tiefighter_elite_mk3 = object_tangible_ship_components_weapon_capacitor_shared_cap_tiefighter_elite_mk3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_tiefighter_elite_mk3",

	attributes = {
		{"currentEnergy", 878.46},
		{"maxEnergy", 878.46},
		{"rechargeRate", 29.28},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 1350},
		{"mass", 46800},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_tiefighter_elite_mk3, "object/tangible/ship/components/weapon_capacitor/cap_tiefighter_elite_mk3.iff")
