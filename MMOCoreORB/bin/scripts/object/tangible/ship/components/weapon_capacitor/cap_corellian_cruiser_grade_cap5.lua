object_tangible_ship_components_weapon_capacitor_cap_corellian_cruiser_grade_cap5 = object_tangible_ship_components_weapon_capacitor_shared_cap_corellian_cruiser_grade_cap5:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_corellian_cruiser_grade_cap5",

	attributes = {
		{"currentEnergy", 698.775},
		{"maxEnergy", 698.775},
		{"rechargeRate", 27.951},
		{"currentHitpoints", 981.151},
		{"maximumHitpoints", 981.151},
		{"maximumArmorHitpoints", 490.576},
		{"currentArmorHitpoints", 490.576},
		{"efficiency", 1},
		{"energyMaintenance", 1200},
		{"mass", 18720},
		{"reverseEngineeringLevel", 7},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_corellian_cruiser_grade_cap5, "object/tangible/ship/components/weapon_capacitor/cap_corellian_cruiser_grade_cap5.iff")
