object_tangible_ship_components_weapon_capacitor_cap_novaldex_sarlacc_s1 = object_tangible_ship_components_weapon_capacitor_shared_cap_novaldex_sarlacc_s1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_novaldex_sarlacc_s1",

	attributes = {
		{"currentEnergy", 787.5},
		{"maxEnergy", 787.5},
		{"rechargeRate", 31.5},
		{"currentHitpoints", 236.25},
		{"maximumHitpoints", 236.25},
		{"maximumArmorHitpoints", 118.125},
		{"currentArmorHitpoints", 118.125},
		{"efficiency", 1},
		{"energyMaintenance", 1050},
		{"mass", 1837.5},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_novaldex_sarlacc_s1, "object/tangible/ship/components/weapon_capacitor/cap_novaldex_sarlacc_s1.iff")
