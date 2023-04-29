object_tangible_ship_components_weapon_capacitor_cap_corellian_standard = object_tangible_ship_components_weapon_capacitor_shared_cap_corellian_standard:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_corellian_standard",

	attributes = {
		{"currentEnergy", 605},
		{"maxEnergy", 605},
		{"rechargeRate", 24.2},
		{"currentHitpoints", 634.8},
		{"maximumHitpoints", 634.8},
		{"maximumArmorHitpoints", 317.4},
		{"currentArmorHitpoints", 317.4},
		{"efficiency", 1},
		{"energyMaintenance", 1100},
		{"mass", 6875},
		{"reverseEngineeringLevel", 5},
	},

	modifiers = {
		{"maxEnergy", 0.25},
		{"rechargeRate", 0.25},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.25},
		{"mass", 0.18},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_corellian_standard, "object/tangible/ship/components/weapon_capacitor/cap_corellian_standard.iff")
