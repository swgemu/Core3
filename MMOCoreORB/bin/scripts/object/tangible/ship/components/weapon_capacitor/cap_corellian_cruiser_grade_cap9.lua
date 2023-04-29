object_tangible_ship_components_weapon_capacitor_cap_corellian_cruiser_grade_cap9 = object_tangible_ship_components_weapon_capacitor_shared_cap_corellian_cruiser_grade_cap9:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_corellian_cruiser_grade_cap9",

	attributes = {
		{"currentEnergy", 1048.16},
		{"maxEnergy", 1048.16},
		{"rechargeRate", 41.927},
		{"currentHitpoints", 1541.81},
		{"maximumHitpoints", 1541.81},
		{"maximumArmorHitpoints", 770.905},
		{"currentArmorHitpoints", 770.905},
		{"efficiency", 1},
		{"energyMaintenance", 1200},
		{"mass", 32760},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_corellian_cruiser_grade_cap9, "object/tangible/ship/components/weapon_capacitor/cap_corellian_cruiser_grade_cap9.iff")
