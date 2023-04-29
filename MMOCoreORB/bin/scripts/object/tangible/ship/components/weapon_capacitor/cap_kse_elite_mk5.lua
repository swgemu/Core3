object_tangible_ship_components_weapon_capacitor_cap_kse_elite_mk5 = object_tangible_ship_components_weapon_capacitor_shared_cap_kse_elite_mk5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_kse_elite_mk5",

	attributes = {
		{"currentEnergy", 768.652},
		{"maxEnergy", 768.652},
		{"rechargeRate", 30.744},
		{"currentHitpoints", 1155.4},
		{"maximumHitpoints", 1155.4},
		{"maximumArmorHitpoints", 577.7},
		{"currentArmorHitpoints", 577.7},
		{"efficiency", 1},
		{"energyMaintenance", 900},
		{"mass", 42300},
		{"reverseEngineeringLevel", 10},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_kse_elite_mk5, "object/tangible/ship/components/weapon_capacitor/cap_kse_elite_mk5.iff")
