object_tangible_ship_components_weapon_capacitor_cap_kessel_rebel_taim_hypercharger = object_tangible_ship_components_weapon_capacitor_shared_cap_kessel_rebel_taim_hypercharger:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_kessel_rebel_taim_hypercharger",

	attributes = {
		{"currentEnergy", 732.05},
		{"maxEnergy", 732.05},
		{"rechargeRate", 29.28},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 1200},
		{"mass", 46800},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maxEnergy", 0.25},
		{"rechargeRate", 0.25},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.25},
		{"mass", 0.18},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_kessel_rebel_taim_hypercharger, "object/tangible/ship/components/weapon_capacitor/cap_kessel_rebel_taim_hypercharger.iff")
