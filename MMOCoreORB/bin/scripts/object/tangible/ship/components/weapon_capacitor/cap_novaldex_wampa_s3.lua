object_tangible_ship_components_weapon_capacitor_cap_novaldex_wampa_s3 = object_tangible_ship_components_weapon_capacitor_shared_cap_novaldex_wampa_s3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_novaldex_wampa_s3",

	attributes = {
		{"currentEnergy", 805.255},
		{"maxEnergy", 805.255},
		{"rechargeRate", 32.208},
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
		{"maxEnergy", 0.2},
		{"rechargeRate", 0.1},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_novaldex_wampa_s3, "object/tangible/ship/components/weapon_capacitor/cap_novaldex_wampa_s3.iff")
