object_tangible_ship_components_weapon_capacitor_cap_corellian_tuned_cruiser_grade_cap1 = object_tangible_ship_components_weapon_capacitor_shared_cap_corellian_tuned_cruiser_grade_cap1:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_corellian_tuned_cruiser_grade_cap1",

	attributes = {
		{"currentEnergy", 825},
		{"maxEnergy", 825},
		{"rechargeRate", 33},
		{"currentHitpoints", 225},
		{"maximumHitpoints", 225},
		{"maximumArmorHitpoints", 112.5},
		{"currentArmorHitpoints", 112.5},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 1750},
		{"reverseEngineeringLevel", 2},
	},

	modifiers = {
		{"maxEnergy", 0.2},
		{"rechargeRate", 0.1},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_corellian_tuned_cruiser_grade_cap1, "object/tangible/ship/components/weapon_capacitor/cap_corellian_tuned_cruiser_grade_cap1.iff")
