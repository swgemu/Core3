object_tangible_ship_components_weapon_capacitor_cap_qualdex_conservator_qx5 = object_tangible_ship_components_weapon_capacitor_shared_cap_qualdex_conservator_qx5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_qualdex_conservator_qx5",

	attributes = {
		{"currentEnergy", 658.845},
		{"maxEnergy", 658.845},
		{"rechargeRate", 26.352},
		{"currentHitpoints", 1100.38},
		{"maximumHitpoints", 1100.38},
		{"maximumArmorHitpoints", 550.19},
		{"currentArmorHitpoints", 550.19},
		{"efficiency", 1},
		{"energyMaintenance", 1200},
		{"mass", 39000},
		{"reverseEngineeringLevel", 9},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_qualdex_conservator_qx5, "object/tangible/ship/components/weapon_capacitor/cap_qualdex_conservator_qx5.iff")
