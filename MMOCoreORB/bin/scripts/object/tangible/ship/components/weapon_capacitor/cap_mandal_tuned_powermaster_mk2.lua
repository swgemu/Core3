object_tangible_ship_components_weapon_capacitor_cap_mandal_tuned_powermaster_mk2 = object_tangible_ship_components_weapon_capacitor_shared_cap_mandal_tuned_powermaster_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_mandal_tuned_powermaster_mk2",

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
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_mandal_tuned_powermaster_mk2, "object/tangible/ship/components/weapon_capacitor/cap_mandal_tuned_powermaster_mk2.iff")
