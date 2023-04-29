object_tangible_ship_components_weapon_capacitor_cap_corellian_deluxe_cruiser_grade_cap2 = object_tangible_ship_components_weapon_capacitor_shared_cap_corellian_deluxe_cruiser_grade_cap2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_corellian_deluxe_cruiser_grade_cap2",

	attributes = {
		{"currentEnergy", 825},
		{"maxEnergy", 825},
		{"rechargeRate", 33},
		{"currentHitpoints", 517.5},
		{"maximumHitpoints", 517.5},
		{"maximumArmorHitpoints", 258.75},
		{"currentArmorHitpoints", 258.75},
		{"efficiency", 1},
		{"energyMaintenance", 1050},
		{"mass", 4593.75},
		{"reverseEngineeringLevel", 4},
	},

	modifiers = {
		{"maxEnergy", 0.25},
		{"rechargeRate", 0.25},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.25},
		{"mass", 0.18},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_corellian_deluxe_cruiser_grade_cap2, "object/tangible/ship/components/weapon_capacitor/cap_corellian_deluxe_cruiser_grade_cap2.iff")
