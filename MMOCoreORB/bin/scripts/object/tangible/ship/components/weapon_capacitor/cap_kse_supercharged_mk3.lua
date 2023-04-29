object_tangible_ship_components_weapon_capacitor_cap_kse_supercharged_mk3 = object_tangible_ship_components_weapon_capacitor_shared_cap_kse_supercharged_mk3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_kse_supercharged_mk3",

	attributes = {
		{"currentEnergy", 862.125},
		{"maxEnergy", 862.125},
		{"rechargeRate", 38.115},
		{"currentHitpoints", 952.2},
		{"maximumHitpoints", 952.2},
		{"maximumArmorHitpoints", 476.1},
		{"currentArmorHitpoints", 476.1},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 11471.2},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_kse_supercharged_mk3, "object/tangible/ship/components/weapon_capacitor/cap_kse_supercharged_mk3.iff")
