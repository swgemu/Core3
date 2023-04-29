object_tangible_ship_components_weapon_capacitor_cap_mandal_powermaster_mk4 = object_tangible_ship_components_weapon_capacitor_shared_cap_mandal_powermaster_mk4:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_mandal_powermaster_mk4",

	attributes = {
		{"currentEnergy", 665.5},
		{"maxEnergy", 665.5},
		{"rechargeRate", 26.62},
		{"currentHitpoints", 934.43},
		{"maximumHitpoints", 934.43},
		{"maximumArmorHitpoints", 467.215},
		{"currentArmorHitpoints", 467.215},
		{"efficiency", 1},
		{"energyMaintenance", 1150},
		{"mass", 17940},
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

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_mandal_powermaster_mk4, "object/tangible/ship/components/weapon_capacitor/cap_mandal_powermaster_mk4.iff")
