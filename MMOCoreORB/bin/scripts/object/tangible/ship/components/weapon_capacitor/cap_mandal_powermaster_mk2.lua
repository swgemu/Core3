object_tangible_ship_components_weapon_capacitor_cap_mandal_powermaster_mk2 = object_tangible_ship_components_weapon_capacitor_shared_cap_mandal_powermaster_mk2:new {
	templateType = SHIPCOMPONENT,

	componentDataName = "cap_mandal_powermaster_mk2",

	attributes = {
		{"currentEnergy", 495},
		{"maxEnergy", 495},
		{"rechargeRate", 19.8},
		{"currentHitpoints", 310.5},
		{"maximumHitpoints", 310.5},
		{"maximumArmorHitpoints", 155.25},
		{"currentArmorHitpoints", 155.25},
		{"efficiency", 1},
		{"energyMaintenance", 950},
		{"mass", 2375},
		{"reverseEngineeringLevel", 3},
	},

	modifiers = {
		{"maxEnergy", 0.23},
		{"rechargeRate", 0.2},
		{"maximumArmorHitpoints", 0.05},
		{"energyMaintenance", 0.22},
		{"mass", 0.13},
	},
}

ObjectTemplates:addTemplate(object_tangible_ship_components_weapon_capacitor_cap_mandal_powermaster_mk2, "object/tangible/ship/components/weapon_capacitor/cap_mandal_powermaster_mk2.iff")
