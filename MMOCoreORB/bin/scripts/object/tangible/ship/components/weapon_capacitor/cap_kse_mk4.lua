object_tangible_ship_components_weapon_capacitor_cap_kse_mk4 = object_tangible_ship_components_weapon_capacitor_shared_cap_kse_mk4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_kse_mk4",

	attributes = {
		{"currentEnergy", 465.85},
		{"maxEnergy", 465.85},
		{"rechargeRate", 18.634},
		{"currentHitpoints", 654.101},
		{"maximumHitpoints", 654.101},
		{"maximumArmorHitpoints", 327.051},
		{"currentArmorHitpoints", 327.051},
		{"efficiency", 1},
		{"energyMaintenance", 850},
		{"mass", 13260},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_kse_mk4, "object/tangible/ship/components/weapon_capacitor/cap_kse_mk4.iff")
