object_tangible_ship_components_weapon_capacitor_cap_tiefighter_elite_mk2 = object_tangible_ship_components_weapon_capacitor_shared_cap_tiefighter_elite_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_tiefighter_elite_mk2",

	attributes = {
		{"currentEnergy", 816.75},
		{"maxEnergy", 816.75},
		{"rechargeRate", 32.67},
		{"currentHitpoints", 856.98},
		{"maximumHitpoints", 856.98},
		{"maximumArmorHitpoints", 428.49},
		{"currentArmorHitpoints", 428.49},
		{"efficiency", 1},
		{"energyMaintenance", 1000},
		{"mass", 10925},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_tiefighter_elite_mk2, "object/tangible/ship/components/weapon_capacitor/cap_tiefighter_elite_mk2.iff")
