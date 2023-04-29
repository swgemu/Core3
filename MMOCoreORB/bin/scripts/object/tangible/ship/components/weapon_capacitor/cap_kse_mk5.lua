object_tangible_ship_components_weapon_capacitor_cap_kse_mk5 = object_tangible_ship_components_weapon_capacitor_shared_cap_kse_mk5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_kse_mk5",

	attributes = {
		{"currentEnergy", 622.242},
		{"maxEnergy", 622.242},
		{"rechargeRate", 24.888},
		{"currentHitpoints", 1045.36},
		{"maximumHitpoints", 1045.36},
		{"maximumArmorHitpoints", 522.68},
		{"currentArmorHitpoints", 522.68},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 44850},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_kse_mk5, "object/tangible/ship/components/weapon_capacitor/cap_kse_mk5.iff")
