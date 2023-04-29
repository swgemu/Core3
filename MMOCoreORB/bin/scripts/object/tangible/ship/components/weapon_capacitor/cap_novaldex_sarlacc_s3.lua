object_tangible_ship_components_weapon_capacitor_cap_novaldex_sarlacc_s3 = object_tangible_ship_components_weapon_capacitor_shared_cap_novaldex_sarlacc_s3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_novaldex_sarlacc_s3",

	attributes = {
		{"currentEnergy", 574.75},
		{"maxEnergy", 574.75},
		{"rechargeRate", 25.41},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 6562.5},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_novaldex_sarlacc_s3, "object/tangible/ship/components/weapon_capacitor/cap_novaldex_sarlacc_s3.iff")
