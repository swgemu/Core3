object_tangible_ship_components_weapon_capacitor_cap_corellian_cruiser_grade_cap1 = object_tangible_ship_components_weapon_capacitor_shared_cap_corellian_cruiser_grade_cap1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_corellian_cruiser_grade_cap1",

	attributes = {
		{"currentEnergy", 600},
		{"maxEnergy", 600},
		{"rechargeRate", 20},
		{"currentHitpoints", 150},
		{"maximumHitpoints", 150},
		{"maximumArmorHitpoints", 75},
		{"currentArmorHitpoints", 75},
		{"efficiency", 1},
		{"energyMaintenance", 1200},
		{"mass", 1000},
		{"reverseEngineeringLevel", 1},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_corellian_cruiser_grade_cap1, "object/tangible/ship/components/weapon_capacitor/cap_corellian_cruiser_grade_cap1.iff")
