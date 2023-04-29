object_tangible_ship_components_weapon_capacitor_cap_novaldex_experimental_sarlacc_s1 = object_tangible_ship_components_weapon_capacitor_shared_cap_novaldex_experimental_sarlacc_s1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_novaldex_experimental_sarlacc_s1",

	attributes = {
		{"currentEnergy", 550},
		{"maxEnergy", 550},
		{"rechargeRate", 22},
		{"currentHitpoints", 345},
		{"maximumHitpoints", 345},
		{"maximumArmorHitpoints", 172.5},
		{"currentArmorHitpoints", 172.5},
		{"efficiency", 1},
		{"energyMaintenance", 1050},
		{"mass", 2625},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maxEnergy", 0.25},
		{"rechargeRate", 0.25},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.25},
		{"mass", 0.18},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_novaldex_experimental_sarlacc_s1, "object/tangible/ship/components/weapon_capacitor/cap_novaldex_experimental_sarlacc_s1.iff")
