object_tangible_ship_components_weapon_capacitor_cap_novaldex_wampa_s2 = object_tangible_ship_components_weapon_capacitor_shared_cap_novaldex_wampa_s2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_novaldex_wampa_s2",

	attributes = {
		{"currentEnergy", 948.338},
		{"maxEnergy", 948.338},
		{"rechargeRate", 41.927},
		{"currentHitpoints", 1401.65},
		{"maximumHitpoints", 1401.65},
		{"maximumArmorHitpoints", 700.823},
		{"currentArmorHitpoints", 700.823},
		{"efficiency", 1},
		{"energyMaintenance", 1200},
		{"mass", 30030},
		{"reverseEngineeringLevel", 8},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_novaldex_wampa_s2, "object/tangible/ship/components/weapon_capacitor/cap_novaldex_wampa_s2.iff")
