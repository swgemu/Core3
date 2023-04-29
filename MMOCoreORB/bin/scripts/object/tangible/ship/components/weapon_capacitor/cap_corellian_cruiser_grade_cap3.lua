object_tangible_ship_components_weapon_capacitor_cap_corellian_cruiser_grade_cap3 = object_tangible_ship_components_weapon_capacitor_shared_cap_corellian_cruiser_grade_cap3:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_corellian_cruiser_grade_cap3",

	attributes = {
		{"currentEnergy", 1089},
		{"maxEnergy", 1089},
		{"rechargeRate", 36.3},
		{"currentHitpoints", 952.2},
		{"maximumHitpoints", 952.2},
		{"maximumArmorHitpoints", 476.1},
		{"currentArmorHitpoints", 476.1},
		{"efficiency", 1},
		{"energyMaintenance", 1300},
		{"mass", 12017.5},
		{"reverseEngineeringLevel", 6},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_corellian_cruiser_grade_cap3, "object/tangible/ship/components/weapon_capacitor/cap_corellian_cruiser_grade_cap3.iff")
