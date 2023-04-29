object_tangible_ship_components_weapon_capacitor_cap_qualdex_conservator_qx1 = object_tangible_ship_components_weapon_capacitor_shared_cap_qualdex_conservator_qx1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_qualdex_conservator_qx1",

	attributes = {
		{"currentEnergy", 574.75},
		{"maxEnergy", 574.75},
		{"rechargeRate", 22.99},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 5937.5},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_qualdex_conservator_qx1, "object/tangible/ship/components/weapon_capacitor/cap_qualdex_conservator_qx1.iff")
