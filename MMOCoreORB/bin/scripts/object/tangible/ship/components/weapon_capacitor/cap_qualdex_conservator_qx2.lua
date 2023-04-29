object_tangible_ship_components_weapon_capacitor_cap_qualdex_conservator_qx2 = object_tangible_ship_components_weapon_capacitor_shared_cap_qualdex_conservator_qx2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_qualdex_conservator_qx2",

	attributes = {
		{"currentEnergy", 907.5},
		{"maxEnergy", 907.5},
		{"rechargeRate", 43.56},
		{"currentHitpoints", 952.2},
		{"maximumHitpoints", 952.2},
		{"maximumArmorHitpoints", 476.1},
		{"currentArmorHitpoints", 476.1},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 12017.5},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.1},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_qualdex_conservator_qx2, "object/tangible/ship/components/weapon_capacitor/cap_qualdex_conservator_qx2.iff")
