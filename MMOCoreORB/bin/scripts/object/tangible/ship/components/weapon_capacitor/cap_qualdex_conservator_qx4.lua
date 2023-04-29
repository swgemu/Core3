object_tangible_ship_components_weapon_capacitor_cap_qualdex_conservator_qx4 = object_tangible_ship_components_weapon_capacitor_shared_cap_qualdex_conservator_qx4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_qualdex_conservator_qx4",

	attributes = {
		{"currentEnergy", 848.512},
		{"maxEnergy", 848.512},
		{"rechargeRate", 33.941},
		{"currentHitpoints", 1331.56},
		{"maximumHitpoints", 1331.56},
		{"maximumArmorHitpoints", 665.781},
		{"currentArmorHitpoints", 665.781},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_qualdex_conservator_qx4, "object/tangible/ship/components/weapon_capacitor/cap_qualdex_conservator_qx4.iff")
