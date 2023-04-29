object_tangible_ship_components_weapon_capacitor_cap_novaldex_sarlacc_s2 = object_tangible_ship_components_weapon_capacitor_shared_cap_novaldex_sarlacc_s2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_novaldex_sarlacc_s2",

	attributes = {
		{"currentEnergy", 783.75},
		{"maxEnergy", 783.75},
		{"rechargeRate", 34.65},
		{"currentHitpoints", 517.5},
		{"maximumHitpoints", 517.5},
		{"maximumArmorHitpoints", 258.75},
		{"currentArmorHitpoints", 258.75},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 4375},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_novaldex_sarlacc_s2, "object/tangible/ship/components/weapon_capacitor/cap_novaldex_sarlacc_s2.iff")
