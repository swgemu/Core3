object_tangible_ship_components_weapon_capacitor_cap_qualdex_conservator_q3 = object_tangible_ship_components_weapon_capacitor_shared_cap_qualdex_conservator_q3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_qualdex_conservator_q3",

	attributes = {
		{"currentEnergy", 866.25},
		{"maxEnergy", 866.25},
		{"rechargeRate", 34.65},
		{"currentHitpoints", 569.25},
		{"maximumHitpoints", 569.25},
		{"maximumArmorHitpoints", 284.625},
		{"currentArmorHitpoints", 284.625},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 4812.5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_qualdex_conservator_q3, "object/tangible/ship/components/weapon_capacitor/cap_qualdex_conservator_q3.iff")
